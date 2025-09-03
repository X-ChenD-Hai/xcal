#pragma once

#include <xcal/public.h>

#include <xcal/camera/core/abs_camera.hpp>
#include <xcal/property/scalar.hpp>
#include <xcal/property/vec.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::camera {
class XCAL_API PerspectiveCamera : public AbsCamera {
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

    const xcmath::mat<float_t, 4, 4>& projection_matrix() const override;
    bool_t projection_is_updated() const override;

   private:
    /* 你的实现里这部分逻辑正确 */
    void update_projection_matrix() const;
};

}  // namespace xcal::camera
