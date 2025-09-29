/**
 * @file listui.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-09-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <xcal/public.h>

#include <xcal/render/impl/opengl/ui/imguirender.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::render::opengl::ui {
class XCAL_API ListUi : public ImGuiUiRender {
   private:
    xcmath::vec3<float_t> vec3f_tmp_;
    bool show_{true};
    float_t tmp_;

   public:
    using ImGuiUiRender::ImGuiUiRender;
    void render_ui() override;

   private:
    bool render_vec3f_edit(const xcmath::vec3<float_t>& vec3f,
                           const char* label, const char* x_label = "x",
                           const char* y_label = "y",
                           const char* z_label = "z");
    void render_obj(ObjectHandle& obj);
    void render_camera(CameraHandle& cam);
    void render_animation(AnimationHandle& anim);
    void render_timeline(TimelineHandle& timeline);

   public:
    ListUi(const ListUi&) = delete;
    ListUi(ListUi&&) = delete;
    ListUi& operator=(const ListUi&) = delete;
    ListUi& operator=(ListUi&&) = delete;
};
}  // namespace xcal::render::opengl::ui