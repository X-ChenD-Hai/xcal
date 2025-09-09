#include <xcal/camera/core/abs_camera.hpp>
#undef OUT  // undefine OUT macro to avoid conflict with xcal::OUT
#define ROLE Camera
#define LABEL AbsCamera
#include <xcal/utils/logmacrohelper.inc>
void xcal::camera::AbsCamera::update_view_matrix() const {
    if (!view_should_update()) return;

    using vec3 = xcmath::vec<float_t, 3>;
    const vec3 eye = position_.value();
    const vec3 center = target_.value();
    const vec3 up = up_.value();

    const vec3 f = (center - eye).normalize();
    const vec3 r = f.cross(up).normalize();
    const vec3 u = r.cross(f);

    auto& V = view_matrix_cache_;
    V = xcmath::mat<float_t, 4, 4>{0.0f};

    // 行主序 look-at
    V[0][0] = r.x();
    V[0][1] = r.y();
    V[0][2] = r.z();
    V[0][3] = -r.dot(eye);
    V[1][0] = u.x();
    V[1][1] = u.y();
    V[1][2] = u.z();
    V[1][3] = -u.dot(eye);
    V[2][0] = -f.x();
    V[2][1] = -f.y();
    V[2][2] = -f.z();
    V[2][3] = f.dot(eye);
    V[3][3] = 1.0f;

    position_.reset_changed();
    target_.reset_changed();
    up_.reset_changed();
    view_or_projection_has_changed_ = true;
}
xcal::bool_t xcal::camera::AbsCamera::view_should_update() const {
    return position_.is_changed() || target_.is_changed() || up_.is_changed();
};
xcal::bool_t xcal::camera::AbsCamera::should_update() const {
    if (projection_should_update() || view_should_update() ||
        view_or_projection_has_changed_)
        _D("should_update(): "
           << (projection_should_update() ? "projection should update" : "")
           << (view_should_update() ? "view should update" : "")
           << (view_or_projection_has_changed_
                   ? "view or projection has changed"
                   : ""));
    return projection_should_update() || view_should_update() ||
           view_or_projection_has_changed_;
};
const xcmath::mat<float_t, 4, 4>& xcal::camera::AbsCamera::pv_matrix() const {
    if (should_update()) {
        pv_matrix_cache_ = projection_matrix() ^ view_matrix();
        view_or_projection_has_changed_ = false;
    }
    return pv_matrix_cache_;
}
void xcal::camera::AbsCamera::projection_has_changed() const {
    view_or_projection_has_changed_ = true;
}
const xcmath::mat<float_t, 4, 4>& xcal::camera::AbsCamera::view_matrix() const {
    update_view_matrix();
    return view_matrix_cache_;
}
