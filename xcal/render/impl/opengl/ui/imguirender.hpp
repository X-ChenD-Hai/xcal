/**
 * @file imguirender.hpp
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

#include <memory>
#include <xcal/render/impl/opengl/ui/context.hpp>
#include <xcal/render/impl/opengl/ui/imguibackend.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::render::opengl::ui {
class XCAL_API ImGuiUiRender : public Context {
   private:
    std::unique_ptr<ImGuiBackend> backend_;

   public:
    void init() override;
    void deinit() override;
    void before_swap_buffers() override;
    void render() override;

   public:
    virtual void render_ui() = 0;

   public:
    explicit ImGuiUiRender(std::unique_ptr<ImGuiBackend> backend,
                           OpenGLRender *renderer)
        : Context(renderer), backend_(std::move(backend)) {}
    ~ImGuiUiRender() override = default;

   public:
    ImGuiUiRender(const ImGuiUiRender &) = delete;
    ImGuiUiRender(ImGuiUiRender &&) = delete;
    ImGuiUiRender &operator=(const ImGuiUiRender &) = delete;
    ImGuiUiRender &operator=(ImGuiUiRender &&) = delete;
};
}  // namespace xcal::render::opengl::ui