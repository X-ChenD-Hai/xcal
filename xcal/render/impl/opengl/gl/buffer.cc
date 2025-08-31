#include <xcal/render/impl/opengl/utils/glbindingincludehelper.inc>
//
#include <xcal/render/impl/opengl/gl/buffer.hpp>

xcal::render::opengl::GL::Buffer::Buffer(_gl GLenum target) : target_(target) {}
xcal::render::opengl::GL::Buffer::~Buffer() {
    if (is_valid()) _gl glDeleteBuffers(1, &vbo_);
    vbo_ = 0;
    size_ = 0;
    target_ = _gl GLenum{};
}
void xcal::render::opengl::GL::Buffer::bind() {
    _gl glBindBuffer(target_, vbo_);
};

void xcal::render::opengl::GL::Buffer::bind_as(_gl GLenum target) {
    _gl glBindBuffer(target, vbo_);
}
void xcal::render::opengl::GL::Buffer::buffer_data(const void *data,
                                                   _gl GLuint size,
                                                   _gl GLenum usage) {
    if (target_ == 0) target_ = _gl GL_ARRAY_BUFFER;
    if (vbo_ == 0) _gl glGenBuffers(1, &vbo_);
    bind();
    _gl glBufferData(target_, size, data, usage);
    size_ = size;
}
void xcal::render::opengl::GL::Buffer::get_buffer_data(
    std::vector<char> &data) {
    data.resize(size_);
    _gl glGetBufferSubData(target_, 0, size_, data.data());
}
void xcal::render::opengl::GL::Buffer::get_buffer_data(std::vector<char> &data,
                                                       _gl GLenum target) {
    data.resize(size_);
    _gl glGetBufferSubData(target, 0, size_, data.data());
}
void xcal::render::opengl::GL::Buffer::destroy() {
    if (is_valid()) _gl glDeleteBuffers(1, &vbo_);
}