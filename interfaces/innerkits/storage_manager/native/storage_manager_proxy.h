/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef OHOS_STORAGE_MANAGER_STORAGE_MANAGER_PROXY_H
#define OHOS_STORAGE_MANAGER_STORAGE_MANAGER_PROXY_H

#include "iremote_proxy.h"
#include "istorage_manager.h"

namespace OHOS {
namespace StorageManager {
class StorageManagerProxy : public IRemoteProxy<IStorageManager> {
public:
    explicit StorageManagerProxy(const sptr<IRemoteObject>& impl)
        : IRemoteProxy<IStorageManager>(impl) {}
    ~StorageManagerProxy() override {}

    int32_t PrepareAddUser(int32_t userId, uint32_t flags) override;
    int32_t RemoveUser(int32_t userId, uint32_t flags) override;
    int32_t PrepareStartUser(int32_t userId) override;
    int32_t StopUser(int32_t userId) override;
    int32_t GetFreeSizeOfVolume(std::string volumeUuid, int64_t &freeSize) override;
    int32_t GetTotalSizeOfVolume(std::string volumeUuid, int64_t &totalSize) override;
    int32_t GetBundleStats(std::string pkgName, BundleStats &bundleStats) override;
    int32_t GetSystemSize(int64_t &systemSize) override;
    int32_t GetTotalSize(int64_t &totalSize) override;
    int32_t GetFreeSize(int64_t &freeSize) override;
    int32_t GetUserStorageStats(StorageStats &storageStats) override;
    int32_t GetUserStorageStats(int32_t userId, StorageStats &storageStats) override;
    int32_t GetUserStorageStatsByType(int32_t userId, StorageStats &storageStats, std::string type) override;
    int32_t GetCurrentBundleStats(BundleStats &bundleStats) override;
    int32_t NotifyVolumeCreated(VolumeCore vc) override;
    int32_t NotifyVolumeMounted(std::string volumeId, int32_t fsType, std::string fsUuid,
                             std::string path, std::string description) override;
    int32_t NotifyVolumeStateChanged(std::string volumeId, VolumeState state) override;
    int32_t Mount(std::string volumeId) override;
    int32_t Unmount(std::string volumeId) override;
    int32_t GetAllVolumes(std::vector<VolumeExternal> &vecOfVol) override;
    int32_t NotifyDiskCreated(Disk disk) override;
    int32_t NotifyDiskDestroyed(std::string diskId) override;
    int32_t Partition(std::string diskId, int32_t type) override;
    int32_t GetAllDisks(std::vector<Disk> &vecOfDisk) override;
    int32_t GetVolumeByUuid(std::string fsUuid, VolumeExternal &vc) override;
    int32_t GetVolumeById(std::string volumeId, VolumeExternal &vc) override;
    int32_t SetVolumeDescription(std::string fsUuid, std::string description) override;
    int32_t Format(std::string volumeId, std::string fsType) override;
    int32_t GetDiskById(std::string diskId, Disk &disk) override;

    // fscrypt api
    int32_t GenerateUserKeys(uint32_t userId, uint32_t flags) override;
    int32_t DeleteUserKeys(uint32_t userId) override;
    int32_t UpdateUserAuth(uint32_t userId, uint64_t secureUid,
                           const std::vector<uint8_t> &token,
                           const std::vector<uint8_t> &oldSecret,
                           const std::vector<uint8_t> &newSecret) override;
    int32_t ActiveUserKey(uint32_t userId,
                          const std::vector<uint8_t> &token,
                          const std::vector<uint8_t> &secret) override;
    int32_t InactiveUserKey(uint32_t userId) override;
    int32_t LockUserScreen(uint32_t userId) override;
    int32_t UnlockUserScreen(uint32_t userId) override;
    int32_t UpdateKeyContext(uint32_t userId) override;

    // app file share api
    std::vector<int32_t> CreateShareFile(const std::vector<std::string> &uriList,
                                        uint32_t tokenId, uint32_t flag) override;
    int32_t DeleteShareFile(uint32_t tokenId, const std::vector<std::string> &uriList) override;

    int32_t SetBundleQuota(const std::string &bundleName, int32_t uid, const std::string &bundleDataDirPath,
        int32_t limitSizeMb) override;

private:
    static inline BrokerDelegator<StorageManagerProxy> delegator_;
    int32_t SendRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option);
};
} // StorageManager   
} // OHOS

#endif // OHOS_STORAGE_MANAGER_STORAGE_MANAGER_PROXY_H
