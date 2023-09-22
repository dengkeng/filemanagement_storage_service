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
#ifndef STORAGE_SERVICE_CONSTANTS_H
#define STORAGE_SERVICE_CONSTANTS_H

#include <map>

namespace OHOS {
namespace StorageService {
const int START_USER_ID = 100;
const int MAX_USER_ID = 1099;
const int UID_FILE_MANAGER = 1006;
const int32_t USER_CONST = 10000;
}

namespace StorageDaemon {
constexpr uint32_t GLOBAL_USER_ID = 0;

static const std::string EL1 = "el1";
static const std::string EL2 = "el2";
enum KeyType {
    EL1_KEY = 1,
    EL2_KEY = 2,
};
static std::map<std::string, KeyType> EL_DIR_MAP = {
    {EL1, EL1_KEY},
    {EL2, EL2_KEY},
};

enum QuotaIdType {
    USERID,
    GRPID,
    PRJID
};
}
}

#endif // STORAGE_SERVICE_CONSTANTS_H