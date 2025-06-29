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
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h> // For joinThreadPool
#include <android/binder/Manager.h> // For AServiceManager::addService

// Include the generated AIDL header
#include <vendor/lineage/touch/ITouchscreenGesture.h>
#include "TouchscreenGesture.h" // Your implementation class

using vendor::lineage::touch::ITouchscreenGesture;
using vendor::lineage::touch::implementation::TouchscreenGesture; // Assuming your implementation is in this namespace

int main() {
    // Enable AIBinder C++ backend for libbinder
    // This is often needed for new AIDL services.
    ABinderProcess_set
    ProcessState::self()->set,
    ABinderProcess_set
    // Old way for binder setup, replaced by AServiceManager::addService
    // android::hardware::configureRpcThreadpool(1, true /*callerWillJoin*/);

    android::sp<TouchscreenGesture> gestureService = new TouchscreenGesture();

    // Register the service with AServiceManager
    if (AServiceManager_addService(gestureService->asBinder().get(),
                                   ITouchscreenGesture::descriptor) != STATUS_OK) {
        LOG(ERROR) << "Cannot register touchscreen gesture HAL service.";
        return 1;
    }

    LOG(INFO) << "Touchscreen HAL service ready.";

    // Start the binder thread pool and join it
    IPCThreadState::self()->joinThreadPool();

    LOG(ERROR) << "Touchscreen HAL service failed to join thread pool.";
    return 1;
}