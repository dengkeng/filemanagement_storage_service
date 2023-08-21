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

#include "ipc/storage_daemon_proxy.h"
#include "ipc/storage_daemon_ipc_interface_code.h"
#include "storage_service_errno.h"
#include "storage_service_log.h"

namespace OHOS {
namespace StorageDaemon {
StorageDaemonProxy::StorageDaemonProxy(const sptr<IRemoteObject> &impl) : IRemoteProxy<IStorageDaemon>(impl)
{}

int32_t StorageDaemonProxy::Shutdown()
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    return SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::SHUTDOWN), data, reply, option);
}

int32_t StorageDaemonProxy::Mount(std::string volId, uint32_t flags)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteString(volId)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteUint32(flags)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::MOUNT), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::UMount(std::string volId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteString(volId)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::UMOUNT), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::Check(std::string volId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteString(volId)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::CHECK), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::Format(std::string volId, std::string fsType)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteString(volId)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteString(fsType)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::FORMAT), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::Partition(std::string diskId, int32_t type)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteString(diskId)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteInt32(type)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::PARTITION), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::SetVolumeDescription(std::string volId, std::string description)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteString(volId)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteString(description)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::SET_VOL_DESC), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::PrepareUserDirs(int32_t userId, uint32_t flags)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteInt32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteUint32(flags)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::PREPARE_USER_DIRS), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::DestroyUserDirs(int32_t userId, uint32_t flags)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteInt32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteUint32(flags)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::DESTROY_USER_DIRS), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::StartUser(int32_t userId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteInt32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::START_USER), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::StopUser(int32_t userId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteInt32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::STOP_USER), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadUint32();
}

int32_t StorageDaemonProxy::InitGlobalKey(void)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::INIT_GLOBAL_KEY), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadUint32();
}

int32_t StorageDaemonProxy::InitGlobalUserKeys(void)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    LOGI("start");
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::INIT_GLOBAL_USER_KEYS), data, reply,
        option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadUint32();
}

int32_t StorageDaemonProxy::GenerateUserKeys(uint32_t userId, uint32_t flags)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    LOGI("start");
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteUint32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }
    if (!data.WriteUint32(flags)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::CREATE_USER_KEYS), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadUint32();
}

int32_t StorageDaemonProxy::DeleteUserKeys(uint32_t userId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteUint32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }
    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::DELETE_USER_KEYS), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::UpdateUserAuth(uint32_t userId, uint64_t secureUid,
                                           const std::vector<uint8_t> &token,
                                           const std::vector<uint8_t> &oldSecret,
                                           const std::vector<uint8_t> &newSecret)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteUint32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }
    if (!data.WriteUint64(secureUid)) {
        return E_WRITE_PARCEL_ERR;
    }
    if (!data.WriteUInt8Vector(token)) {
        return E_WRITE_PARCEL_ERR;
    }
    if (!data.WriteUInt8Vector(oldSecret)) {
        return E_WRITE_PARCEL_ERR;
    }
    if (!data.WriteUInt8Vector(newSecret)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::UPDATE_USER_AUTH), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::ActiveUserKey(uint32_t userId,
                                          const std::vector<uint8_t> &token,
                                          const std::vector<uint8_t> &secret)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteUint32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }
    if (!data.WriteUInt8Vector(token)) {
        return E_WRITE_PARCEL_ERR;
    }
    if (!data.WriteUInt8Vector(secret)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::ACTIVE_USER_KEY), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::InactiveUserKey(uint32_t userId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteUint32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }
    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::INACTIVE_USER_KEY), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::UpdateKeyContext(uint32_t userId)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteUint32(userId)) {
        return E_WRITE_PARCEL_ERR;
    }
    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::UPDATE_KEY_CONTEXT), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::CreateShareFile(std::string uri, uint32_t tokenId, uint32_t flag)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteString(uri)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteUint32(tokenId)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteUint32(flag)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::CREATE_SHARE_FILE), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::DeleteShareFile(uint32_t tokenId, std::vector<std::string>sharePathList)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_ASYNC);

    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteUint32(tokenId)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteStringVector(sharePathList)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::DELETE_SHARE_FILE), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::SetBundleQuota(const std::string &bundleName, int32_t uid,
    const std::string &bundleDataDirPath, int32_t limitSizeMb)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteString(bundleName)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteInt32(uid)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteString(bundleDataDirPath)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteInt32(limitSizeMb)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::SET_BUNDLE_QUOTA), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    return reply.ReadInt32();
}

int32_t StorageDaemonProxy::GetOccupiedSpace(int32_t idType, int32_t id, int64_t &size)
{
    MessageParcel data;
    MessageParcel reply;
    MessageOption option(MessageOption::TF_SYNC);
    if (!data.WriteInterfaceToken(StorageDaemonProxy::GetDescriptor())) {
        return E_WRITE_DESCRIPTOR_ERR;
    }

    if (!data.WriteInt32(idType)) {
        return E_WRITE_PARCEL_ERR;
    }

    if (!data.WriteInt32(id)) {
        return E_WRITE_PARCEL_ERR;
    }

    int err = SendRequest(static_cast<int32_t>(StorageDaemonInterfaceCode::GET_SPACE), data, reply, option);
    if (err != E_OK) {
        return err;
    }

    err = reply.ReadInt32();
    if (err != E_OK) {
        return err;
    }
    size = reply.ReadInt64();
    return E_OK;
}

int32_t StorageDaemonProxy::SendRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        LOGE("remote is nullptr, code = %{public}d", code);
        return E_REMOTE_IS_NULLPTR;
    }

    int32_t result = remote->SendRequest(code, data, reply, option);
    if (result != E_OK) {
        LOGE("failed to SendRequest, code = %{public}d, result = %{public}d", code, result);
        return result;
    }

    return E_OK;
}
} // StorageDaemon
} // OHOS
