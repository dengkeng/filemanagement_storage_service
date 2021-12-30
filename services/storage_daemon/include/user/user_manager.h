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

#ifndef OHOS_STORAGE_DAEMON_USER_MANAGER_H
#define OHOS_STORAGE_DAEMON_USER_MANAGER_H

#include <string>
#include <vector>
#include <sys/types.h>
#include <nocopyable.h>

namespace OHOS {
namespace StorageDaemon {
struct DirInfo {
    const std::string path;
    mode_t mode;
    uid_t uid;
    gid_t gid;
};

constexpr uid_t OID_ROOT = 0;
constexpr uid_t OID_SYSTEM = 1000;

class UserManager final {
public:
    virtual ~UserManager() = default;
    static UserManager* Instance();
    int32_t PrepareUserDirs(int32_t userId, uint32_t flags);
    int32_t DestroyUserDirs(int32_t userId, uint32_t flags);
    int32_t StartUser(int32_t userId);
    int32_t StopUser(int32_t userId);

private:
    UserManager();
    bool PrepareEl1RootDirs(int32_t userId);
    bool PrepareEl1SubDirs(int32_t userId);
    bool PrepareEl2RootDirs(int32_t userId);
    bool PrepareEl2SubDirs(int32_t userId);
    bool PrepareUserHmdfsDirs(int32_t userId);
    bool DestroyUserEl1Dirs(int32_t userId);
    bool DestroyUserEl2Dirs(int32_t userId);
    bool DestroyUserHmdfsDirs(int32_t userId);
    DISALLOW_COPY_AND_MOVE(UserManager);

    static UserManager* instance_;
    const std::vector<DirInfo> el1RootDirVec_;
    const std::vector<DirInfo> el1SubDirVec_;
    const std::vector<DirInfo> el2RootDirVec_;
    const std::vector<DirInfo> el2SubDirVec_;
    const std::vector<DirInfo> hmdfsDirVec_;
    const std::string hmdfsSource_;
    const std::string hmdfsTarget_;
};
} // STORAGE_DAEMON
} // OHOS

#endif // OHOS_STORAGE_DAEMON_USER_MANAGER_H