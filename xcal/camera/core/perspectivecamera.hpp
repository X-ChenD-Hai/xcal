#pragma once

#include <xcal/public.h>

#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/property/scalar.hpp>
#include <xcal/property/vec.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::camera {
class PerspectiveCamera : public AbsCamera {
   private:
    /* 投影参数 */
    property::Scalar fov_;
    property::Scalar aspect_;
    property::Scalar near_;
    property::Scalar far_;

    /* 缓存 */
    mutable xcmath::mat<float_t, 4, 4> projection_matrix_cache_;

   public:
    PerspectiveCamera(float fov, float aspect, float near, float far)
        : fov_(fov), aspect_(aspect), near_(near), far_(far) {}

   public:
    /* 公共访问器方法 */
    property::Scalar& fov() { return fov_; }
    const property::Scalar& fov() const { return fov_; }

    property::Scalar& aspect() { return aspect_; }
    const property::Scalar& aspect() const { return aspect_; }

    property::Scalar& near() { return near_; }
    const property::Scalar& near() const { return near_; }

    property::Scalar& far() { return far_; }
    const property::Scalar& far() const { return far_; }

    const xcmath::mat<float_t, 4, 4>& projection_matrix() const {
        update_projection_matrix();
        return projection_matrix_cache_;
    }

   private:
    /* 你的实现里这部分逻辑正确 */
    void update_projection_matrix() const {
        if (!fov_.is_changed() && !aspect_.is_changed() &&
            !near_.is_changed() && !far_.is_changed())
            return;

        const float fov_rad = fov_.value() * xcmath::PI / 180.0f;
        const float tan_half = std::tan(fov_rad * 0.5f);
        const float n = near_.value();
        const float f = far_.value();
        const float a = aspect_.value();

        auto& P = projection_matrix_cache_;
        P = xcmath::mat<float_t, 4, 4>{0.0f};

        // 行主序
        P[0][0] = 1.0f / (a * tan_half);
        P[1][1] = 1.0f / tan_half;
        P[2][2] = -(f + n) / (f - n);
        P[2][3] = -2.0f * f * n / (f - n);
        P[3][2] = -1.0f;
        // 其余元素保持 0

        fov_.reset_changed();
        aspect_.reset_changed();
        near_.reset_changed();
        far_.reset_changed();
    }
};

}  // namespace xcal::camera
