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
#ifndef STORAGE_DAEMON_UTILS_ERRNO_H
#define STORAGE_DAEMON_UTILS_ERRNO_H

namespace OHOS {
namespace StorageDaemon {
constexpr int32_t E_ERR = -1;

enum ErrNo {
    E_OK = 0,
    E_PERMISSION_DENIED = 1,  // no permission
    E_IPC_ERROR = 2,          // ipc error
    E_EXIST = 3,              // exist
    E_WRONG_TYPE = 4,         // wrong file type
    E_USER_STATE = 5,            // wrong user state
    E_NON_EXIST = 6,            // no such user
    E_PREPARE_DIR = 7,         // failed to prepare dir
    E_DESTROY_DIR = 8,         // failed to destroy dir
    E_MOUNT,        // mount error
    E_UMOUNT,       // umount error
};
}
}

#endif // STORAGE_DAEMON_UTILS_ERRNO_H