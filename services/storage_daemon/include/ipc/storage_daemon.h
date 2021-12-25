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

#ifndef OHOS_STORAGE_DAEMON_STORAGE_DAEMON_H
#define OHOS_STORAGE_DAEMON_STORAGE_DAEMON_H

#include "ipc/storage_daemon_stub.h"
#include <mutex>

namespace OHOS {
namespace StorageDaemon {
class StorageDaemon : public StorageDaemonStub {
public:
    StorageDaemon() = default;
    virtual ~StorageDaemon() = default;

    virtual int32_t Shutdown() override;
    virtual int32_t Mount(std::string volId, uint32_t flags) override;
    virtual int32_t UMount(std::string volId) override;
    virtual int32_t Check(std::string volId) override;
    virtual int32_t Format(std::string voldId) override;

    virtual int32_t AddUser(int32_t userId) override;
    virtual int32_t RemoveUser(int32_t userId) override;
    virtual int32_t StartUser(int32_t userId) override;
    virtual int32_t StopUser(int32_t userId) override;
    virtual int32_t PrepareUserDirs(int32_t userId, uint32_t flags) override;
    virtual int32_t DestroyUserDirs(int32_t userId, uint32_t flags) override;

private:
    std::mutex mutex_;
};
} // StorageDaemon
} // OHOS

#endif // OHOS_STORAGE_DAEMON_STORAGE_DAEMON_H
