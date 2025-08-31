#include <glbinding/gl/gl.h>
#ifndef __gl_h_
#define __gl_h_
#endif  //
#include <render/impl/opengl/gl/vertexarrayobject.hpp>
using namespace ::gl;

xcal::render::opengl::GL::VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &vao_);
};
xcal::render::opengl::GL::VertexArrayObject::~VertexArrayObject() {
    if (is_valid()) glDeleteVertexArrays(1, &vao_);
    vao_ = 0;
};
void xcal::render::opengl::GL::VertexArrayObject::bind() {
    glBindVertexArray(vao_);
};
void xcal::render::opengl::GL::VertexArrayObject::unbind() {
    glBindVertexArray(0);
};

xcal::render::opengl::GL::VertexArrayObject &
xcal::render::opengl::GL::VertexArrayObject::operator=(VertexArrayObject &&o) {
    std::swap(vao_, o.vao_);
    return *this;
}
xcal::render::opengl::GL::VertexArrayObject::VertexArrayObject(
    VertexArrayObject &&o) {
    std::swap(vao_, o.vao_);
}
