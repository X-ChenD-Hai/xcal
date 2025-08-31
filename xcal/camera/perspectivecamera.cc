#include <xcal/camera/perspectivecamera.hpp>

void xcal::camera::PerspectiveCamera::update_projection_matrix() const {
    if (!fov_.is_changed() && !aspect_.is_changed() && !near_.is_changed() &&
        !far_.is_changed())
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
