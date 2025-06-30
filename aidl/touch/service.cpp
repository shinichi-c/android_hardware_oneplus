/*
 * Copyright (C) 2019 The LineageOS Project
 *
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

#define LOG_TAG "vendor.lineage.touch-service.oneplus"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>

#include "TouchscreenGesture.h"

using aidl::vendor::lineage::touch::TouchscreenGesture;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<TouchscreenGesture> service = ndk::SharedRefBase::make<TouchscreenGesture>();
    
    const std::string instance = std::string(TouchscreenGesture::descriptor) + "/default";
    binder_status_t status = AServiceManager_addService(service->asBinder().get(), instance.c_str());
    
    if (status != STATUS_OK) {
        LOG(ERROR) << "Cannot register touchscreen gesture HAL service: " << status;
        return 1;
    }

    LOG(INFO) << "Touchscreen HAL service ready: " << instance;
    ABinderProcess_joinThreadPool();
    
    // Should never reach here
    LOG(ERROR) << "Touchscreen HAL service exited unexpectedly";
    return 1;
}