/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "storage/storage_status_service.h"
#include "storage_service_errno.h"
#include "storage_service_log.h"
#include "installd_client.h"
#include "os_account_manager.h"
#include "os_account_constants.h"

using namespace std;

namespace OHOS {
namespace StorageManager {
StorageStatusService::StorageStatusService() {}
StorageStatusService::~StorageStatusService() {}

int StorageStatusService::GetCurrentUserId()
{
    vector<int> osAccountInfos;
    if (AccountSA::OsAccountManager::QueryActiveOsAccountIds(osAccountInfos) == E_OK) {
        if (osAccountInfos.size() > 0) {
            return osAccountInfos[0];
        }
    }
    LOGE("StorageStatusService::An error occurred in querying current os account.");
    return DEFAULT_USER_ID;
}

vector<int64_t> StorageStatusService::GetBundleStats(std::string uuid, std::string pkgName)
{
    vector<int64_t> result = {0, 0, 0};
    int userId = GetCurrentUserId();
    LOGI("StorageStatusService::userId is:%d", userId);
    if (userId < 0 || userId > AccountSA::Constants::MAX_USER_ID) {
        LOGI("StorageStatusService::Invaild userId.");
        return result;
    }
    vector<int64_t> bundleStats;
    int errorcode = AppExecFwk::InstalldClient::GetInstance()->GetBundleStats(pkgName, userId, bundleStats);
    if (bundleStats.size() != dataDir.size() || errorcode != E_OK) {
        LOGE("StorageStatusService::An error occurred in querying bundle stats.");
        return result;
    }
    for (int i = 0; i < bundleStats.size(); i++) {
        if (bundleStats[i] == E_ERR) {
            LOGE("StorageStatusService::Failed to query %s data.", dataDir[i].c_str());
            bundleStats[i] = 0;
        }
    }
    result[APPSIZE] = bundleStats[APP];
    result[CACHESIZE] = bundleStats[CACHE];
    result[DATASIZE] = bundleStats[LOCAL] + bundleStats[DISTRIBUTED] + bundleStats[DATABASE];
    return result;
}
} // StorageManager
} // OHOS
