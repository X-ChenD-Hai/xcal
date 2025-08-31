#pragma once
#include <xcal/public.h>

#include <xcal/render/impl/opengl/core/typedef.hpp>

namespace xcal::render::opengl::GL {
class VertexArrayObject {
    friend class ::xcal::render::opengl::object::Object;

    VertexArrayObject(const VertexArrayObject &) = delete;
    VertexArrayObject(VertexArrayObject &&o);
    VertexArrayObject &operator=(const VertexArrayObject &) = delete;
    VertexArrayObject &operator=(VertexArrayObject &&o);

   private:
    gl::GLuint vao_ = 0;

   private:
    VertexArrayObject();
    ~VertexArrayObject();
    VertexArrayObject(gl::GLuint vao) : vao_(vao) {}

   public:
    void bind();
    void unbind();
    bool is_valid() { return vao_ != 0; };
    void swap(VertexArrayObject &o) { std::swap(vao_, o.vao_); }
};
}  // namespace xcal::render::opengl::GL