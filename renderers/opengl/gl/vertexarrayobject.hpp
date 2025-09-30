#pragma once
#include XCAL_OPENGL_RENDERER_CONFIG_HEADER

#include <core/typedef.hpp>

namespace xcal::render::opengl::GL {
class XCAL_OPENGL_RENDERER_API VertexArrayObject {
    friend class ::xcal::render::opengl::object::Object;

    VertexArrayObject(const VertexArrayObject &) = delete;
    VertexArrayObject(VertexArrayObject &&o);
    VertexArrayObject &operator=(const VertexArrayObject &) = delete;
    VertexArrayObject &operator=(VertexArrayObject &&o);

   private:
    gl::GLuint vao_ = 0;

   public:
    VertexArrayObject();
    ~VertexArrayObject();
    explicit VertexArrayObject(gl::GLuint vao) : vao_(vao) {}

   public:
    void bind() const;
    static void unbind();
    bool is_valid() const { return vao_ != 0; };

   public:
    void swap(VertexArrayObject &o) { std::swap(vao_, o.vao_); }
};
}  // namespace xcal::render::opengl::GL