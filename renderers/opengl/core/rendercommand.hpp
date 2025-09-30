/**
 * @file rendercommand.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2025-09-28
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <core/typedef.hpp>
#include <cstddef>
#include <vector>
#include <xcal/render/utils/resourcedistributor.hpp>

namespace xcal::render::opengl::GL {
class GLObject {
   public:
    void vao(size_t id);
    void push_vbo(size_t id);
    void vbo(size_t id);
    void push_ebo(size_t id);
    void ebo(size_t id);
};

struct RenderCommand {
    gl::GLuint vao;
    std::vector<gl::GLuint> program;
    gl::GLenum mode;
    size_t count;
};
}  // namespace xcal::render::opengl::GL