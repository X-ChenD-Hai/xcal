#pragma once
#include <public.h>

#include <render/impl/opengl/core/typedef.hpp>
using namespace gl;
namespace xcal::render::opengl::GL {
class VertexArrayObject {
    friend class ::xcal::render::opengl::object::Object;

    VertexArrayObject(const VertexArrayObject &) = delete;
    VertexArrayObject(VertexArrayObject &&o);
    VertexArrayObject &operator=(const VertexArrayObject &) = delete;
    VertexArrayObject &operator=(VertexArrayObject &&o);

   private:
    GLuint vao_ = 0;

   private:
    VertexArrayObject();
    ~VertexArrayObject();
    VertexArrayObject(GLuint vao) : vao_(vao) {}

   public:
    void bind();
    void unbind();
    bool is_valid() { return vao_ != 0; };
    void swap(VertexArrayObject &o) { std::swap(vao_, o.vao_); }
};
}  // namespace xcal::render::opengl::GL