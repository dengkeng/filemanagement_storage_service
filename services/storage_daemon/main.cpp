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

#include "ipc/storage_daemon.h"
#include "ipc_skeleton.h"
#include "iservice_registry.h"

using namespace OHOS;

int main()
{
    //TODO define ID in system_ability_definition.h
    int said = 0;

    do {
        auto samgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
        if (samgr != nullptr) {
            sptr<StorageDaemon::StorageDaemon> sd = new StorageDaemon::StorageDaemon();
            samgr->AddSystemAbility(said, sd);
            break;
        }
    } while (true);

    IPCSkeleton::JoinWorkThread();

    return 0;
}
