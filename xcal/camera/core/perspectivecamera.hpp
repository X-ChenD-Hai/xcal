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
    /* 视图参数 */
    property::Vec<float_t, 3> position_{0.f, 0.f, -1.f};
    property::Vec<float_t, 3> target_{0.f, 0.f, 0.f};
    property::Vec<float_t, 3> up_{0.f, 1.f, 0.f};

    /* 缓存 */
    mutable xcmath::mat<float_t, 4, 4> projection_matrix_cache_;
    mutable xcmath::mat<float_t, 4, 4> view_matrix_cache_;
    mutable bool projection_dirty_ = true;
    mutable bool view_dirty_ = true;

   public:
    PerspectiveCamera(float fov, float aspect, float near, float far)
        : fov_(fov), aspect_(aspect), near_(near), far_(far) {}

    /* 每次渲染前调用，判断是否需要更新缓存 */
    void update_matrices() const {
        if (fov_.is_changed() || aspect_.is_changed() || near_.is_changed() ||
            far_.is_changed()) {
            update_projection_matrix();
            projection_dirty_ = false;
        }
        if (position_.is_changed() || target_.is_changed() ||
            up_.is_changed()) {
            update_view_matrix();
            view_dirty_ = false;
        }
    }

    /* 获取投影矩阵 P */
    const xcmath::mat<float_t, 4, 4>& projection_matrix() const {
        if (projection_dirty_) update_matrices();
        return projection_matrix_cache_;
    }

   public:
    /* 获取视图矩阵 V */
    const xcmath::mat<float_t, 4, 4>& view_matrix() const {
        if (view_dirty_) update_matrices();
        return view_matrix_cache_;
    }

    /* 公共访问器方法 */
    property::Scalar& fov() { return fov_; }
    const property::Scalar& fov() const { return fov_; }

    property::Scalar& aspect() { return aspect_; }
    const property::Scalar& aspect() const { return aspect_; }

    property::Scalar& near() { return near_; }
    const property::Scalar& near() const { return near_; }

    property::Scalar& far() { return far_; }
    const property::Scalar& far() const { return far_; }

    property::Vec<float_t, 3>& position() { return position_; }
    const property::Vec<float_t, 3>& position() const { return position_; }

    property::Vec<float_t, 3>& target() { return target_; }
    const property::Vec<float_t, 3>& target() const { return target_; }

    property::Vec<float_t, 3>& up() { return up_; }
    const property::Vec<float_t, 3>& up() const { return up_; }

   private:
    /* 你的实现里这部分逻辑正确 */
    void update_projection_matrix() const {
        const float fov_rad = fov_.value() * xcmath::PI / 180.f;
        const float tan_half = std::tan(fov_rad * 0.5f);
        const float z_range = far_.value() - near_.value();
        const float r_aspect = aspect_.value();

        auto& P = projection_matrix_cache_;
        P = xcmath::mat<float_t, 4, 4>{0.f};
        P[0][0] = 1.f / (r_aspect * tan_half);
        P[1][1] = 1.f / tan_half;
        P[2][2] = -(far_.value() + near_.value()) / z_range;
        P[3][2] = -(2.f * far_.value() * near_.value()) / z_range;
        P[2][3] = -1.f;

        fov_.reset_changed();
        aspect_.reset_changed();
        near_.reset_changed();
        far_.reset_changed();
    }

    /* 新增：根据 look-at 方法计算视图矩阵 V */
    void update_view_matrix() const {
        using vec3 = xcmath::vec<float_t, 3>;
        vec3 f = (target_.value() - position_.value()).normalize();
        vec3 r = f.cross(up_.value()).normalize();
        vec3 u = r.cross(f);

        auto& V = view_matrix_cache_;
        V = xcmath::mat<float_t, 4, 4>{0.f};

        V[0][0] = r.x();
        V[0][1] = u.x();
        V[0][2] = -f.x();
        V[1][0] = r.y();
        V[1][1] = u.y();
        V[1][2] = -f.y();
        V[2][0] = r.z();
        V[2][1] = u.z();
        V[2][2] = -f.z();

        V[0][3] = -r.dot(position_.value());
        V[1][3] = -u.dot(position_.value());
        V[2][3] = f.dot(position_.value());
        V[3][3] = 1.f;

        position_.reset_changed();
        target_.reset_changed();
        up_.reset_changed();
    }
};
}  // namespace xcal::camera
