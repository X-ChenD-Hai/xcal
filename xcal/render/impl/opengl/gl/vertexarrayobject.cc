#include <xcal/render/impl/opengl/utils/glbindingincludehelper.inc>
//
#include <xcal/render/impl/opengl/gl/vertexarrayobject.hpp>

xcal::render::opengl::GL::VertexArrayObject::VertexArrayObject() {
    _gl glGenVertexArrays(1, &vao_);
};
xcal::render::opengl::GL::VertexArrayObject::~VertexArrayObject() {
    if (is_valid()) _gl glDeleteVertexArrays(1, &vao_);
    vao_ = 0;
};
void xcal::render::opengl::GL::VertexArrayObject::bind() const {
    _gl glBindVertexArray(vao_);
};
void xcal::render::opengl::GL::VertexArrayObject::unbind() const {
    _gl glBindVertexArray(0);
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
