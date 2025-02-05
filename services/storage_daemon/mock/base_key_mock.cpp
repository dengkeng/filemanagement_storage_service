/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "base_key_mock.h"

#include "base_key.h"

using namespace std;

using namespace OHOS::StorageDaemon;

BaseKey::BaseKey(const std::string &dir, uint8_t keyLen) : dir_(dir), keyLen_(keyLen),
    keyEncryptType_(KeyEncryptType::KEY_CRYPT_HUKS)
{
}

bool BaseKey::InitKey(bool needGenerateKey)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->InitKey(needGenerateKey);
}

#ifdef USER_CRYPTO_MIGRATE_KEY
bool BaseKey::StoreKey(const UserAuth &auth, bool needGenerateShield)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->StoreKey(auth, needGenerateShield);
}
#else
bool BaseKey::StoreKey(const UserAuth &auth)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->StoreKey(auth);
}
#endif

bool BaseKey::ClearKey(const std::string &mnt)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->ClearKey(mnt);
}

bool BaseKey::UpdateKey(const std::string &keypath)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->UpdateKey(keypath);
}

bool BaseKey::RestoreKey(const UserAuth &auth)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->RestoreKey(auth);
}

bool BaseKey::UpgradeKeys()
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->UpgradeKeys();
}

bool BaseKey::DecryptKeyBlob(const UserAuth &auth, const std::string &keyPath, KeyBlob &planKey,
                             KeyBlob &decryptedKey)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->DecryptKeyBlob(auth, keyPath, planKey, decryptedKey);
}

bool BaseKey::EncryptKeyBlob(const UserAuth &auth, const std::string &keyPath, KeyBlob &planKey,
                             KeyBlob &encryptedKey)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->EncryptKeyBlob(auth, keyPath, planKey, encryptedKey);
}

bool BaseKey::RenameKeyPath(const std::string &keyPath)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->RenameKeyPath(keyPath);
}
    
void BaseKey::ClearMemoryKeyCtx()
{
    return;
}

void BaseKey::WipingActionDir(std::string &path)
{
    return;
}

bool BaseKey::GetOriginKey(KeyBlob &originKey)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->GetOriginKey(originKey);
}

bool BaseKey::SaveKeyBlob(const KeyBlob &blob, const std::string &path)
{
    if (IBaseKeyMoc::baseKeyMoc == nullptr) {
        return false;
    }
    return IBaseKeyMoc::baseKeyMoc->SaveKeyBlob(blob, path);
}
