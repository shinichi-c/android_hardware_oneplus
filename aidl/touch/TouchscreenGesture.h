#pragma once

#include <aidl/vendor/lineage/touch/BnTouchscreenGesture.h>
#include <aidl/vendor/lineage/touch/Gesture.h>
#include <map>
#include <string>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

class TouchscreenGesture : public BnTouchscreenGesture {
public:
    struct GestureInfo {
        int keycode;
        std::string name;
        std::string path;
    };

    ::ndk::ScopedAStatus getSupportedGestures(std::vector<Gesture>* out) override;
    ::ndk::ScopedAStatus setGestureEnabled(const Gesture& gesture, bool enabled) override;

private:
    static const std::map<int32_t, GestureInfo> kGestureInfoMap;
};

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl