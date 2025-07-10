/*
 * Copyright (C) 2019-2021 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "TouchscreenGestureService"

#include "TouchscreenGesture.h"
#include <android-base/logging.h>
#include <unistd.h>
#include <fstream>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

using ::ndk::ScopedAStatus;

const std::map<int32_t, TouchscreenGesture::GestureInfo> TouchscreenGesture::kGestureInfoMap = {
    {0, {251, "Two fingers down swipe", "/proc/touchpanel/double_swipe_enable"}},
    {1, {252, "Down arrow", "/proc/touchpanel/down_arrow_enable"}},
    {2, {253, "Left arrow", "/proc/touchpanel/left_arrow_enable"}},
    {3, {254, "Right arrow", "/proc/touchpanel/right_arrow_enable"}},
    {4, {247, "Letter M", "/proc/touchpanel/letter_m_enable"}},
    {5, {250, "Letter O", "/proc/touchpanel/letter_o_enable"}},
    {6, {248, "Letter S", "/proc/touchpanel/letter_s_enable"}},
    {7, {246, "Letter W", "/proc/touchpanel/letter_w_enable"}},
    {8, {255, "Single Tap", "/proc/touchpanel/single_tap_enable"}},
};

ScopedAStatus TouchscreenGesture::getSupportedGestures(std::vector<Gesture>* out) {
    for (const auto& [id, info] : kGestureInfoMap) {
        if (access(info.path.c_str(), F_OK) == 0) {
            Gesture gesture;
            gesture.id = id;
            gesture.name = info.name;
            gesture.keycode = info.keycode;
            out->push_back(gesture);
        }
    }
    return ScopedAStatus::ok();
}

ScopedAStatus TouchscreenGesture::setGestureEnabled(const Gesture& gesture, bool enabled) {
    auto it = kGestureInfoMap.find(gesture.id);
    if (it == kGestureInfoMap.end()) {
        return ScopedAStatus::fromExceptionCode(EX_UNSUPPORTED_OPERATION);
    }

    std::ofstream file(it->second.path);
    file << (enabled ? "1" : "0");
    
    if (file.fail()) {
        LOG(ERROR) << "Failed to write to " << it->second.path;
        return ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }
    
    return ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl