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
    // Internal gesture information structure
    struct GestureInfo {
        int keycode;
        const char* name;
        const char* path;
    };

    ::ndk::ScopedAStatus getSupportedGestures(std::vector<Gesture>* out) override;
    ::ndk::ScopedAStatus setGestureEnabled(const Gesture& gesture, 
                                           bool enabled,
                                           bool* success) override;

  private:
    static const std::map<int32_t, GestureInfo> kGestureInfoMap;
};

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl