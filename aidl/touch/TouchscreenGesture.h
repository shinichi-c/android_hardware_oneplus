#pragma once

#include <aidl/vendor/lineage/touch/BnTouchscreenGesture.h>
#include <aidl/vendor/lineage/touch/Gesture.h>
#include <map>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

class TouchscreenGesture : public BnTouchscreenGesture {
public:
    ::ndk::ScopedAStatus getSupportedGestures(std::vector<Gesture>* out) override;
    ::ndk::ScopedAStatus setGestureEnabled(int32_t gestureId, bool enabled, bool* success) override;

private:
    struct GestureInfo {
        int keycode;
        std::string name;
        std::string path;
    };
    static const std::map<int32_t, GestureInfo> kGestureInfoMap;
};

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl