#pragma once

#include <xcal/camera/core/abs_camera.hpp>
#include <xcmath/xcmath.hpp>
namespace xcal::camera {
class PerspectiveCamera : public AbsCamera {
   private:
    float fov_;
    float aspect_;
    float near_;
    float far_;

   public:
    PerspectiveCamera(const float fov, const float aspect, const float near,
                      const float far)
        : fov_(fov), aspect_(aspect), near_(near), far_(far) {}
};
}  // namespace xcal::camera