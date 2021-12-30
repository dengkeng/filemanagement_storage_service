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

#ifndef OHOS_STORAGE_MANAGER_STORAGE_DAEMON_COMMUNICATION_H
#define OHOS_STORAGE_MANAGER_STORAGE_DAEMON_COMMUNICATION_H

#include <singleton.h>
#include <nocopyable.h>
#include "system_ability.h"
#include "ipc/istorage_daemon.h"

namespace OHOS {
namespace StorageManager {

class StorageDaemonCommunication : public NoCopyable {
    DECLARE_DELAYED_SINGLETON(StorageDaemonCommunication);

public:
    int32_t Connect();

    int32_t OnUserCreate(int32_t userId, uint32_t flags);
    int32_t OnUserDelete(int32_t userId, uint32_t flags);
    int32_t PrepareUserStart(int32_t userId);
    int32_t PrepareUserStop(int32_t userId);

private:
    sptr<OHOS::StorageDaemon::IStorageDaemon> storageDaemon_;
};
} // StorageManager
} // OHOS

#endif