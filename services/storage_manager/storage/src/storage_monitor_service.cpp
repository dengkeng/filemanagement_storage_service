/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "storage/storage_monitor_service.h"

#include <cstdlib>
#include <cstring>
#include <mntent.h>
#include <pthread.h>
#include <singleton.h>
#include <sys/statvfs.h>
#include <unordered_set>

#include "cJSON.h"
#include "common_event_data.h"
#include "common_event_manager.h"
#include "storage_service_errno.h"
#include "storage_service_log.h"
#include "storage/bundle_manager_connector.h"
#include "storage/storage_total_status_service.h"
#include "want.h"

namespace OHOS {
namespace StorageManager {
constexpr int32_t CONST_NUM_TWO = 2;
constexpr int32_t CONST_NUM_THREE = 3;
constexpr int32_t CONST_NUM_ONE_HUNDRED = 100;
constexpr int32_t WAIT_THREAD_TIMEOUT_MS = 5;
constexpr int32_t DEFAULT_CHECK_INTERVAL = 60 * 1000; // 60s
constexpr int32_t STORAGE_THRESHOLD_PERCENTAGE = 5; // 5%
constexpr int64_t STORAGE_THRESHOLD_MAX_BYTES = 500 * 1024 * 1024; // 500M
constexpr int64_t STORAGE_THRESHOLD_1G = 1000 * 1024 * 1024; // 1G
constexpr int32_t STORAGE_LEFT_SIZE_THRESHOLD = 10; // 10%
constexpr int32_t SEND_EVENT_INTERVAL = 24; // 24H
const std::string PUBLISH_SYSTEM_COMMON_EVENT = "ohos.permission.PUBLISH_SYSTEM_COMMON_EVENT";
const std::string SMART_BUNDLE_NAME = "com.ohos.hmos.hiviewcare";
const std::string SMART_ACTION = "hicare.event.SMART_NOTIFICATION";
const std::string FAULT_ID_ONE = "845010021";
const std::string FAULT_ID_TWO = "845010022";

StorageMonitorService::StorageMonitorService() {}

StorageMonitorService::~StorageMonitorService()
{
    LOGI("StorageMonitorService Destructor.");
    std::unique_lock<std::mutex> lock(eventMutex_);
    if ((eventHandler_ != nullptr) && (eventHandler_->GetEventRunner() != nullptr)) {
        eventHandler_->RemoveAllEvents();
        eventHandler_->GetEventRunner()->Stop();
    }
    if (eventThread_.joinable()) {
        eventThread_.join();
    }
    eventHandler_ = nullptr;
}

void StorageMonitorService::StartStorageMonitorTask()
{
    LOGI("StorageMonitorService, start deicve storage monitor task.");
    std::unique_lock<std::mutex> lock(eventMutex_);
    if (eventHandler_ == nullptr) {
        eventThread_ = std::thread(&StorageMonitorService::StartEventHandler, this);
        eventCon_.wait_for(lock, std::chrono::seconds(WAIT_THREAD_TIMEOUT_MS), [this] {
            return eventHandler_ != nullptr;
        });
    }

    auto executeFunc = [this] { Execute(); };
    eventHandler_->PostTask(executeFunc, DEFAULT_CHECK_INTERVAL);
}

void StorageMonitorService::StartEventHandler()
{
    pthread_setname_np(pthread_self(), "storage_monitor_task_event");
    auto runner = AppExecFwk::EventRunner::Create(false);
    if (runner == nullptr) {
        LOGE("event runner is nullptr.");
        return;
    }
    {
        std::lock_guard<std::mutex> lock(eventMutex_);
        eventHandler_ = std::make_shared<AppExecFwk::EventHandler>(runner);
    }
    eventCon_.notify_one();
    runner->Run();
}

void StorageMonitorService::Execute()
{
    if (eventHandler_ == nullptr) {
        LOGE("event handler is nullptr.");
        return;
    }
    CheckAndCleanBundleCache();
    auto executeFunc = [this] { Execute(); };
    eventHandler_->PostTask(executeFunc, DEFAULT_CHECK_INTERVAL);
}

void StorageMonitorService::CheckAndCleanBundleCache()
{
    int64_t totalSize;
    int32_t err = DelayedSingleton<StorageTotalStatusService>::GetInstance()->GetTotalSize(totalSize);
    if ((err != E_OK) || (totalSize <= 0)) {
        LOGE("Get device total size failed.");
        return;
    }

    int64_t freeSize;
    err = DelayedSingleton<StorageTotalStatusService>::GetInstance()->GetFreeSize(freeSize);
    if ((err != E_OK) || (freeSize <= 0)) {
        LOGE("Get device free size failed.");
        return;
    }
    if (freeSize < (totalSize * STORAGE_LEFT_SIZE_THRESHOLD) / CONST_NUM_ONE_HUNDRED) {
        CheckAndEventNotify(freeSize, totalSize);
    }
    int64_t lowThreshold = GetLowerThreshold(totalSize);
    if (lowThreshold <= 0) {
        LOGE("Lower threshold value is invalid.");
        return;
    }

    LOGI("Device storage freeSize=%{public}lld, threshold=%{public}lld", static_cast<long long>(freeSize),
        static_cast<long long>(lowThreshold));
    if (freeSize >= (lowThreshold * CONST_NUM_THREE) / CONST_NUM_TWO) {
        LOGI("The cache clean threshold had not been reached, skip this clean task.");
        return;
    }

    auto bundleMgr = DelayedSingleton<BundleMgrConnector>::GetInstance()->GetBundleMgrProxy();
    if (bundleMgr == nullptr) {
        LOGE("Connect bundle manager sa proxy failed.");
        return;
    }
    LOGI("Device storage free size not enough, start clean bundle cache files automatic.");
    auto ret = bundleMgr->CleanBundleCacheFilesAutomatic(lowThreshold * CONST_NUM_TWO);
    if (ret != ERR_OK) {
        LOGE("Invoke bundleMgr interface to clean bundle cache files automatic failed.");
    }
}

int64_t StorageMonitorService::GetLowerThreshold(int64_t totalSize)
{
    int64_t lowBytes = (totalSize * STORAGE_THRESHOLD_PERCENTAGE) / CONST_NUM_ONE_HUNDRED;
    return (lowBytes < STORAGE_THRESHOLD_MAX_BYTES) ? lowBytes : STORAGE_THRESHOLD_MAX_BYTES;
}

void StorageMonitorService::CheckAndEventNotify(int64_t freeSize, int64_t totalSize)
{
    LOGI("StorageMonitorService, start CheckAndEventNotify.");
    auto currentTime = std::chrono::steady_clock::now();
    int32_t duration = static_cast<int32_t>(std::chrono::duration_cast<std::chrono::hours>
            (currentTime - lastNotificationTime_).count());
    LOGI("StorageMonitorService, duration is %{public}d", duration);
    if (duration >= SEND_EVENT_INTERVAL) {
        if (freeSize >= STORAGE_THRESHOLD_1G) {
            SendSmartNotificationEvent(FAULT_ID_ONE);
        } else {
            SendSmartNotificationEvent(FAULT_ID_TWO);
        }
        lastNotificationTime_ = currentTime;
    }
}

void StorageMonitorService::SendSmartNotificationEvent(const std::string &faultId)
{
    LOGI("StorageMonitorService, start SendSmartNotificationEvent.");
    EventFwk::CommonEventPublishInfo publishInfo;
    const std::string permission = PUBLISH_SYSTEM_COMMON_EVENT;
    std::vector<std::string> permissions;
    permissions.emplace_back(permission);
    publishInfo.SetSubscriberPermissions(permissions);
    publishInfo.SetOrdered(false);
    publishInfo.SetSticky(false);
    publishInfo.SetBundleName(SMART_BUNDLE_NAME);

    AAFwk::Want want;
    want.SetAction(SMART_ACTION);
    EventFwk::CommonEventData eventData;
    eventData.SetWant(want);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "faultDescription", faultId.c_str());
    cJSON_AddStringToObject(root, "faultSuggestion", faultId.c_str());

    char *json_string = cJSON_Print(root);
    std::string eventDataStr(json_string);
    eventDataStr.erase(remove(eventDataStr.begin(), eventDataStr.end(), '\n'), eventDataStr.end());
    eventDataStr.erase(remove(eventDataStr.begin(), eventDataStr.end(), '\t'), eventDataStr.end());

    LOGI("send message is %{public}s", eventDataStr.c_str());
    eventData.SetData(eventDataStr);
    cJSON_Delete(root);
    EventFwk::CommonEventManager::PublishCommonEvent(eventData, publishInfo, nullptr);
}
} // StorageManager
} // OHOS
