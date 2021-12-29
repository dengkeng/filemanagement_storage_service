/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef STORAGE_DAEMON_CRYPTO_BASEKEY_H
#define STORAGE_DAEMON_CRYPTO_BASEKEY_H

#include <string>

#include "key_utils.h"

namespace OHOS {
namespace StorageDaemon {
class BaseKey {
public:
    BaseKey() = delete;
    BaseKey(std::string dir);
    ~BaseKey() = default;

    bool InitKey();
    bool StoreKey(const UserAuth &auth);
    bool RestoreKey(const UserAuth &auth);
    bool ActiveKey();
    bool ClearKey();

    KeyInfo keyInfo_;

private:
    bool DoStoreKey(const UserAuth &auth);
    bool GenerateKeyBlob(KeyBlob &blob, const uint32_t size);
    bool SaveKeyBlob(const KeyBlob &blob, const std::string &name);
    bool GenerateAndSaveKeyBlob(KeyBlob &blob, const std::string &name, const uint32_t size);
    bool LoadKeyBlob(KeyBlob &blob, const std::string &name, const uint32_t size);
    bool GenerateKeyDesc();
    bool EncryptKey(const UserAuth &auth);
    bool DecryptKey(const UserAuth &auth);

    std::unique_ptr<char[]> GetRandomBytes(uint32_t size);

    std::string dir_ {};
    KeyContext keyContext_ {};
};
} // namespace StorageDaemon
} // namespace OHOS

#endif // STORAGE_DAEMON_CRYPTO_BASEKEY_H
