#include <xcal/camera/core/abs_camera.hpp>

void xcal::camera::AbsCamera::update_view_matrix() const {
    if (!position_.is_changed() && !target_.is_changed() && !up_.is_changed())
        return;

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
}
