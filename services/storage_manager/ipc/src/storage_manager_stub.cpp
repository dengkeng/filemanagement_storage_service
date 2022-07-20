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

#include "ipc/storage_manager_stub.h"
#include "accesstoken_kit.h"
#include "ipc_skeleton.h"
#include "storage_service_errno.h"
#include "storage_service_log.h"

namespace OHOS {
namespace StorageManager {
const std::string PERMISSION_STORAGE_MANAGER = "ohos.permission.STORAGE_MANAGER";
const std::string PERMISSION_MOUNT_MANAGER = "ohos.permission.MOUNT_UNMOUNT_MANAGER";
const std::string PERMISSION_FORMAT_MANAGER = "ohos.permission.MOUNT_FORMAT_MANAGER";
bool CheckClientPermission(const std::string& permissionStr)
{
    Security::AccessToken::AccessTokenID tokenCaller = IPCSkeleton::GetCallingTokenID();
    int res = Security::AccessToken::AccessTokenKit::VerifyAccessToken(tokenCaller,
        permissionStr);
    if (res == Security::AccessToken::PermissionState::PERMISSION_GRANTED) {
        LOGI("StorageMangaer permissionCheck pass!");
        return true;
    }
    LOGE("StorageManager permissionCheck error, need %{public}s", permissionStr.c_str());
    return false;
}
int32_t StorageManagerStub::OnRemoteRequest(uint32_t code,
    MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    auto remoteDescriptor = data.ReadInterfaceToken();
    if (GetDescriptor() != remoteDescriptor) {
        return E_PERMISSION_DENIED;
    }

    int err = 0;
    switch (code) {
        case PREPARE_ADD_USER:
            HandlePrepareAddUser(data, reply);
            break;
        case REMOVE_USER:
            HandleRemoveUser(data, reply);
            break;
        case PREPARE_START_USER:
            HandlePrepareStartUser(data, reply);
            break;
        case STOP_USER:
            HandleStopUser(data, reply);
            break;
        case GET_TOTAL:
            HandleGetTotal(data, reply);
            break;
        case GET_FREE:
            HandleGetFree(data, reply);
            break;
        case GET_SYSTEM_SIZE:
            HandleGetSystemSize(data, reply);
            break;
        case GET_TOTAL_SIZE:
            HandleGetTotalSize(data, reply);
            break;
        case GET_FREE_SIZE:
            HandleGetFreeSize(data, reply);
            break;
        case GET_CURR_USER_STATS:
            HandleGetCurrUserStorageStats(data, reply);
            break;
        case GET_USER_STATS:
            HandleGetUserStorageStats(data, reply);
            break;
        case GET_CURR_BUNDLE_STATS:
            HandleGetCurrentBundleStats(data, reply);
            break;
        case GET_BUNDLE_STATUS:
            HandleGetBundleStatus(data, reply);
            break;
        case NOTIFY_VOLUME_CREATED:
            HandleNotifyVolumeCreated(data, reply);
            break;
        case NOTIFY_VOLUME_MOUNTED:
            HandleNotifyVolumeMounted(data, reply);
            break;
        case NOTIFY_VOLUME_DESTROYED:
            HandleNotifyVolumeDestroyed(data, reply);
            break;
        case MOUNT:
            HandleMount(data, reply);
            break;
        case UNMOUNT:
            HandleUnmount(data, reply);
            break;
        case GET_ALL_VOLUMES:
            HandleGetAllVolumes(data, reply);
            break;
        case NOTIFY_DISK_CREATED:
            HandleNotifyDiskCreated(data, reply);
            break;
        case NOTIFY_DISK_DESTROYED:
            HandleNotifyDiskDestroyed(data, reply);
            break;
        case PARTITION:
            HandlePartition(data, reply);
            break;
        case GET_ALL_DISKS:
            HandleGetAllDisks(data, reply);
            break;
        case GET_VOL_BY_UUID:
            HandleGetVolumeByUuid(data, reply);
            break;
        case GET_VOL_BY_ID:
            HandleGetVolumeById(data, reply);
            break;
        case SET_VOL_DESC:
            HandleSetVolDesc(data, reply);
            break;
        case FORMAT:
            HandleFormat(data, reply);
            break;
        case GET_DISK_BY_ID:
            HandleGetDiskById(data, reply);
            break;
        case CREATE_USER_KEYS:
            HandleGenerateUserKeys(data, reply);
            break;
        case DELETE_USER_KEYS:
            HandleDeleteUserKeys(data, reply);
            break;
        case UPDATE_USER_AUTH:
            HandleUpdateUserAuth(data, reply);
            break;
        case ACTIVE_USER_KEY:
            HandleActiveUserKey(data, reply);
            break;
        case INACTIVE_USER_KEY:
            HandleInactiveUserKey(data, reply);
            break;
        case UPDATE_KEY_CONTEXT:
            HandleUpdateKeyContext(data, reply);
            break;
        default: {
            LOGI("use IPCObjectStub default OnRemoteRequest");
            err = IPCObjectStub::OnRemoteRequest(code, data, reply, option);
            break;
        }
    }
    return err;
}

int32_t StorageManagerStub::HandlePrepareAddUser(MessageParcel &data, MessageParcel &reply)
{
    int32_t userId = data.ReadInt32();
    uint32_t flags = data.ReadUint32();
    LOGI("StorageManagerStub::HandlePrepareAddUser, userId:%{public}d", userId);
    int err = PrepareAddUser(userId, flags);
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandlePrepareAddUser call PrepareAddUser failed");
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleRemoveUser(MessageParcel &data, MessageParcel &reply)
{
    int32_t userId = data.ReadInt32();
    uint32_t flags = data.ReadUint32();
    LOGI("StorageManagerStub::HandleRemoveUser, userId:%{public}d", userId);
    int err = RemoveUser(userId, flags);
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandleRemoveUser call RemoveUser failed");
        return E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandlePrepareStartUser(MessageParcel &data, MessageParcel &reply)
{
    int32_t userId = data.ReadInt32();
    LOGI("StorageManagerStub::HandlePrepareStartUser, userId:%{public}d", userId);
    int err = PrepareStartUser(userId);
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandlePrepareStartUser call PrepareStartUser failed");
        return E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleStopUser(MessageParcel &data, MessageParcel &reply)
{
    int32_t userId = data.ReadInt32();
    LOGI("StorageManagerStub::HandleStopUser, userId:%{public}d", userId);
    int err = StopUser(userId);
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandleStopUser call StopUser failed");
        return E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetTotal(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    LOGE("StorageManagerStub::HandleGetTotal Begin.");
    std::string volumeId = data.ReadString();
    int64_t totalSize = GetTotalSizeOfVolume(volumeId);
    if (!reply.WriteInt64(totalSize)) {
        LOGE("StorageManagerStub::HandleGetTotal call OnUserDGetTotalSizeOfVolume failed");
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetFree(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string volumeId = data.ReadString();
    int64_t freeSize = GetFreeSizeOfVolume(volumeId);
    if (!reply.WriteInt64(freeSize)) {
        LOGE("StorageManagerStub::HandleGetFree call GetFreeSizeOfVolume failed");
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetBundleStatus(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string pkgName = data.ReadString();
    BundleStats bundleStats = GetBundleStats(pkgName);
    if (!bundleStats.Marshalling(reply)) {
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetSystemSize(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    int64_t systemSize = GetSystemSize();
    if (!reply.WriteInt64(systemSize)) {
        LOGE("StorageManagerStub::HandleGetFree call GetSystemSize failed");
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetTotalSize(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    int64_t totalSize = GetTotalSize();
    if (!reply.WriteInt64(totalSize)) {
        LOGE("StorageManagerStub::HandleGetFree call GetTotalSize failed");
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetFreeSize(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    int64_t freeSize = GetFreeSize();
    if (!reply.WriteInt64(freeSize)) {
        LOGE("StorageManagerStub::HandleGetFree call GetFreeSize failed");
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetCurrUserStorageStats(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    StorageStats storageStats = GetUserStorageStats();
    if (!storageStats.Marshalling(reply)) {
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetUserStorageStats(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    int32_t userId = data.ReadInt32();
    StorageStats storageStats = GetUserStorageStats(userId);
    if (!storageStats.Marshalling(reply)) {
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetCurrentBundleStats(MessageParcel &data, MessageParcel &reply)
{
    BundleStats bundleStats = GetCurrentBundleStats();
    if (!bundleStats.Marshalling(reply)) {
        return  E_IPC_ERROR;
    }
    return E_OK;
}
int32_t StorageManagerStub::HandleGetAllVolumes(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::vector<VolumeExternal> ve = GetAllVolumes();
    uint size = ve.size();
    if (size == 0) {
        LOGE("StorageManagerStub::No volume.");
        if (!reply.WriteUint32(0)) {
            return  E_IPC_ERROR;
        }
        return E_OK;
    }
    if (!reply.WriteUint32(ve.size())) {
        return  E_IPC_ERROR;
    }
    for (uint i = 0; i < size; i++) {
        if (!ve[i].Marshalling(reply)) {
            return  E_IPC_ERROR;
        }
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleNotifyVolumeCreated(MessageParcel &data, MessageParcel &reply)
{
    std::unique_ptr<VolumeCore> vc = VolumeCore::Unmarshalling(data);
    NotifyVolumeCreated(*vc);
    LOGI("StorageManagerStub::HandleNotifyVolumeCreated");
    return E_OK;
}

int32_t StorageManagerStub::HandleNotifyVolumeMounted(MessageParcel &data, MessageParcel &reply)
{
    std::string volumeId = data.ReadString();
    int32_t fsType = data.ReadInt32();
    std::string fsUuid = data.ReadString();
    std::string path = data.ReadString();
    std::string description = data.ReadString();
    NotifyVolumeMounted(volumeId, fsType, fsUuid, path, description);
    LOGI("StorageManagerStub::HandleNotifyVolumeMounted");
    return E_OK;
}

int32_t StorageManagerStub::HandleNotifyVolumeDestroyed(MessageParcel &data, MessageParcel &reply)
{
    std::string volumeId = data.ReadString();
    NotifyVolumeDestroyed(volumeId);
    LOGI("StorageManagerStub::HandleNotifyVolumeDestroyed");
    return E_OK;
}

int32_t StorageManagerStub::HandleMount(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_MOUNT_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string volumeId = data.ReadString();
    int err = Mount(volumeId);
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandleMount call Mount failed");
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleUnmount(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_MOUNT_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string volumeId = data.ReadString();
    int err = Unmount(volumeId);
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandleUnmount call Mount failed");
        return  E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleNotifyDiskCreated(MessageParcel &data, MessageParcel &reply)
{
    auto disk = Disk::Unmarshalling(data);
    NotifyDiskCreated(*disk);
    return E_OK;
}

int32_t StorageManagerStub::HandleNotifyDiskDestroyed(MessageParcel &data, MessageParcel &reply)
{
    std::string diskId = data.ReadString();
    NotifyDiskDestroyed(diskId);
    return E_OK;
}

int32_t StorageManagerStub::HandlePartition(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_FORMAT_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string diskId = data.ReadString();
    int32_t type = data.ReadInt32();
    int err = Partition(diskId, type);
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandlePartition call Partition failed");
        return E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetAllDisks(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::vector<Disk> disks = GetAllDisks();
    uint size = disks.size();
    if (size == 0) {
        LOGE("StorageManagerStub::No Disk.");
        if (!reply.WriteUint32(0)) {
            return  E_IPC_ERROR;
        }
        return E_OK;
    }
    if (!reply.WriteUint32(disks.size())) {
        return  E_IPC_ERROR;
    }
    for (uint i = 0; i < size; i++) {
        if (!disks[i].Marshalling(reply)) {
            return  E_IPC_ERROR;
        }
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetVolumeByUuid(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string fsUuid = data.ReadString();
    VolumeExternal vc;
    int err = GetVolumeByUuid(fsUuid, vc);
    if (!vc.Marshalling(reply)) {
        return E_IPC_ERROR;
    }
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandleGetVolumeByUuid call GetVolumeByUuid failed");
        return E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetVolumeById(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string volId = data.ReadString();
    VolumeExternal vc;
    int err = GetVolumeById(volId, vc);
    if (!vc.Marshalling(reply)) {
        return E_IPC_ERROR;
    }
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandleGetVolumeById call GetVolumeById failed");
        return E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleSetVolDesc(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_MOUNT_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string fsUuid = data.ReadString();
    std::string desc = data.ReadString();
    int err = SetVolumeDescription(fsUuid, desc);
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandleSetVolDesc call SetVolumeDescription failed");
        return E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleFormat(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_FORMAT_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string volId = data.ReadString();
    std::string fsType = data.ReadString();
    int err = Format(volId, fsType);
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandleFormat call Format failed");
        return E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGetDiskById(MessageParcel &data, MessageParcel &reply)
{
    if (!CheckClientPermission(PERMISSION_STORAGE_MANAGER)) {
        return E_PERMISSION_DENIED;
    }
    std::string volId = data.ReadString();
    Disk disk;
    int err = GetDiskById(volId, disk);
    if (!disk.Marshalling(reply)) {
        return E_IPC_ERROR;
    }
    if (!reply.WriteUint32(err)) {
        LOGE("StorageManagerStub::HandleGetDiskById call GetDiskById failed");
        return E_IPC_ERROR;
    }
    return E_OK;
}

int32_t StorageManagerStub::HandleGenerateUserKeys(MessageParcel &data, MessageParcel &reply)
{
    uint32_t userId = data.ReadUint32();
    uint32_t flags = data.ReadUint32();
    int32_t err = GenerateUserKeys(userId, flags);
    if (!reply.WriteInt32(err)) {
        LOGE("Write reply error code failed");
        return E_IPC_ERROR;
    }

    return E_OK;
}

int32_t StorageManagerStub::HandleDeleteUserKeys(MessageParcel &data, MessageParcel &reply)
{
    uint32_t userId = data.ReadUint32();
    int32_t err = DeleteUserKeys(userId);
    if (!reply.WriteInt32(err)) {
        LOGE("Write reply error code failed");
        return E_IPC_ERROR;
    }

    return E_OK;
}

int32_t StorageManagerStub::HandleUpdateUserAuth(MessageParcel &data, MessageParcel &reply)
{
    uint32_t userId = data.ReadUint32();

    std::vector<uint8_t> token, oldSecret, newSecret;
    data.ReadUInt8Vector(&token);
    data.ReadUInt8Vector(&oldSecret);
    data.ReadUInt8Vector(&newSecret);

    int32_t err = UpdateUserAuth(userId, token, oldSecret, newSecret);
    if (!reply.WriteInt32(err)) {
        LOGE("Write reply error code failed");
        return E_IPC_ERROR;
    }

    return E_OK;
}

int32_t StorageManagerStub::HandleActiveUserKey(MessageParcel &data, MessageParcel &reply)
{
    uint32_t userId = data.ReadUint32();

    std::vector<uint8_t> token, secret;
    data.ReadUInt8Vector(&token);
    data.ReadUInt8Vector(&secret);

    int32_t err = ActiveUserKey(userId, token, secret);
    if (!reply.WriteInt32(err)) {
        LOGE("Write reply error code failed");
        return E_IPC_ERROR;
    }

    return E_OK;
}

int32_t StorageManagerStub::HandleInactiveUserKey(MessageParcel &data, MessageParcel &reply)
{
    uint32_t userId = data.ReadUint32();
    int32_t err = InactiveUserKey(userId);
    if (!reply.WriteInt32(err)) {
        LOGE("Write reply error code failed");
        return E_IPC_ERROR;
    }

    return E_OK;
}

int32_t StorageManagerStub::HandleUpdateKeyContext(MessageParcel &data, MessageParcel &reply)
{
    uint32_t userId = data.ReadUint32();
    int32_t err = UpdateKeyContext(userId);
    if (!reply.WriteInt32(err)) {
        LOGE("Write reply error code failed");
        return E_IPC_ERROR;
    }

    return E_OK;
}
} // StorageManager
} // OHOS
