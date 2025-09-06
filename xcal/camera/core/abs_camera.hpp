#pragma once
#include <xcal/public.h>

#include <xcal/camera/core/frame.hpp>
#include <xcal/property/vec.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::camera {
class XCAL_API AbsCamera {
   private:
    /* 视图参数 */
    property::Vec<float_t, 3> position_{0.f, 0.f, -1.f};
    property::Vec<float_t, 3> target_{0.f, 0.f, 0.f};
    property::Vec<float_t, 3> up_{0.f, 1.f, 0.f};
    mutable bool_t view_or_projection_has_changed_{true};
    mutable xcmath::mat<float_t, 4, 4> view_matrix_cache_{
        xcmath::mat<float_t, 4, 4>::eye()};
    mutable xcmath::mat<float_t, 4, 4> pv_matrix_cache_{
        xcmath::mat<float_t, 4, 4>::eye()};

   private:
    void update_view_matrix() const;

   public:
    /* 获取投影矩阵 P */
    property::Vec<float_t, 3>& position() { return position_; }
    const property::Vec<float_t, 3>& position() const { return position_; }

    property::Vec<float_t, 3>& target() { return target_; }
    const property::Vec<float_t, 3>& target() const { return target_; }

    property::Vec<float_t, 3>& up() { return up_; }
    const property::Vec<float_t, 3>& up() const { return up_; }

    template <typename... Args>
    AbsCamera* set_position(Args... args) {
        position_ = {args...};
        return this;
    }
    template <typename... Args>
    AbsCamera* set_target(Args... args) {
        target_ = {args...};
        return this;
    }
    template <typename... Args>
    AbsCamera* set_up(Args... args) {
        up_ = {args...};
        return this;
    }

    /* 获取视图矩阵 V */
    const xcmath::mat<float_t, 4, 4>& view_matrix() const;

   protected:
    void projection_has_changed() const;

   public:
    AbsCamera() {};
    virtual ~AbsCamera() = default;
    virtual const xcmath::mat<float_t, 4, 4>& projection_matrix() const = 0;
    virtual bool_t projection_should_update() const = 0;
    bool_t view_should_update() const;
    bool_t should_update() const;
    const xcmath::mat<float_t, 4, 4>& pv_matrix() const;
};
}  // namespace xcal::camera
template class XCAL_API xcal::property::Vec<float_t, 3>;