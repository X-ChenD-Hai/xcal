#include <render/impl/opengl/utils/glbindingincludehelper.inc>
//
#include <render/impl/opengl/gl/buffer.hpp>

xcal::render::opengl::GL::Buffer::Buffer(GLenum target) : target_(target) {}
xcal::render::opengl::GL::Buffer::~Buffer() {
    if (is_valid()) glDeleteBuffers(1, &vbo_);
    vbo_ = 0;
    size_ = 0;
    target_ = GLenum{};
}
void xcal::render::opengl::GL::Buffer::bind() {
    _gl glBindBuffer(target_, vbo_);
};

void xcal::render::opengl::GL::Buffer::bind_as(GLenum target) {
    _gl glBindBuffer(target, vbo_);
}
void xcal::render::opengl::GL::Buffer::buffer_data(const void *data,
                                                   GLuint size, GLenum usage) {
    if (target_ == 0) target_ = GL_ARRAY_BUFFER;
    if (vbo_ == 0) glGenBuffers(1, &vbo_);
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
                                                       GLenum target) {
    data.resize(size_);
    _gl glGetBufferSubData(target, 0, size_, data.data());
}
void xcal::render::opengl::GL::Buffer::destroy() {
    if (is_valid()) glDeleteBuffers(1, &vbo_);
}