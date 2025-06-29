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

#define LOG_TAG "TouchscreenGestureService"

namespace {

struct GestureInfo {
    int keycode;
    std::string name;
    std::string path;
};

const std::map<int32_t, GestureInfo> kGestureInfoMap = {
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

}  // anonymous namespace

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

using ::ndk::ScopedAStatus;

ScopedAStatus TouchscreenGesture::getSupportedGestures(std::vector<Gesture>* _aidl_return) {
    for (const auto& [id, info] : kGestureInfoMap) {
        if (access(info.path.c_str(), F_OK) == 0) {
            Gesture gesture;
            gesture.id = id;
            gesture.name = info.name;
            gesture.keycode = info.keycode;
            _aidl_return->push_back(std::move(gesture));
        }
    }
    return ScopedAStatus::ok();
}

ScopedAStatus TouchscreenGesture::setGestureEnabled(int32_t gestureId, bool enabled, bool* _aidl_return) {
    auto it = kGestureInfoMap.find(gestureId);
    if (it == kGestureInfoMap.end()) {
        *_aidl_return = false;
        return ScopedAStatus::ok();
    }

    std::ofstream file(it->second.path);
    file << (enabled ? "1" : "0");
    *_aidl_return = !file.fail();
    LOG(DEBUG) << "Wrote file " << it->second.path << " fail " << file.fail();
    return ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl