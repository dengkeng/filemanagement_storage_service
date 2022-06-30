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

#include "volume_core.h"

namespace OHOS {
namespace StorageManager {
VolumeCore::VolumeCore() {}

VolumeCore::VolumeCore(std::string id, int type, std::string diskId)
{
    id_ = id;
    type_ = type;
    diskId_ = diskId;
}

VolumeCore::VolumeCore(std::string id, int type, std::string diskId, int32_t state)
{
    id_ = id;
    type_ = type;
    diskId_ = diskId;
    state_ = state;
}

void VolumeCore::SetState(int32_t state)
{
    state_ = state;
}

std::string VolumeCore::GetId()
{
    return id_;
}

int VolumeCore::GetType()
{
    return type_;
}

std::string VolumeCore::GetDiskId()
{
    return diskId_;
}

int32_t VolumeCore::GetState()
{
    return state_;
}

bool VolumeCore::Marshalling(Parcel &parcel) const
{
    parcel.WriteString(id_);
    parcel.WriteInt32(type_);
    parcel.WriteString(diskId_);
    parcel.WriteInt32(state_);
    parcel.WriteBool(errorFlag_);
    return true;
}

std::unique_ptr<VolumeCore> VolumeCore::Unmarshalling(Parcel &parcel)
{
    auto obj = std::make_unique<VolumeCore>();
    obj->id_ = parcel.ReadString();
    obj->type_ = parcel.ReadInt32();
    obj->diskId_ = parcel.ReadString();
    obj->state_ = parcel.ReadInt32();
    obj->errorFlag_ = parcel.ReadBool();
    return obj;
}
}
}
