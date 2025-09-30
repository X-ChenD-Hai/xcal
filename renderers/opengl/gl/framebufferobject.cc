#include <gl/framebufferobject.hpp>
#include <utils/openglapiloadhelper.inc>

void xcal::render::opengl::GL::FramebufferObject::unbind() {
    _gl glBindFramebuffer(_gl GL_FRAMEBUFFER, 0);
}
xcal::render::opengl::GL::FramebufferObject::FramebufferObject(
    gl::GLuint width, gl::GLuint height, color_format_t color_format,
    pixel_type_t pixel_type)
    : texture_(_gl GL_TEXTURE_2D),
      width_(width),
      height_(height),
      color_format_(color_format),
      pixel_type_(pixel_type) {
    _gl glGenFramebuffers(1, &fbo_);
    _gl glBindFramebuffer(_gl GL_FRAMEBUFFER, fbo_);
    texture_.bind();
    texture_.image_2d(0, color_format_, width_, height_, 0, color_format_,
                      pixel_type_, nullptr);
    texture_.parameteri(_gl GL_TEXTURE_MIN_FILTER, _gl GL_LINEAR);
    texture_.parameteri(_gl GL_TEXTURE_MAG_FILTER, _gl GL_LINEAR);
    texture_.unbind();
    _gl glFramebufferTexture2D(_gl GL_FRAMEBUFFER, _gl GL_COLOR_ATTACHMENT0,
                               _gl GL_TEXTURE_2D, texture_.texture_, 0);
    if (_gl glCheckFramebufferStatus(_gl GL_FRAMEBUFFER) !=
        _gl GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Framebuffer not complete");
    }
};
xcal::render::opengl::GL::FramebufferObject::~FramebufferObject() {
    _gl glDeleteFramebuffers(1, &fbo_);
}
void xcal::render::opengl::GL::FramebufferObject::bind() const {
    _gl glBindFramebuffer(_gl GL_FRAMEBUFFER, fbo_);
}
std::vector<char>
xcal::render::opengl::GL::FramebufferObject::read_pixels_char() const {
    assert(pixel_type_ == pixel_type_t::UNSIGNED_BYTE);
    std::vector<char> pixels(width_ * height_ * 4);
    _gl glReadBuffer(_gl GL_COLOR_ATTACHMENT0);
    _gl glReadPixels(0, 0, width_, height_, _gl GL_RGBA, _gl GL_UNSIGNED_BYTE,
                     pixels.data());
    return pixels;
}
std::vector<float>
xcal::render::opengl::GL::FramebufferObject::read_pixels_float() const {
    assert(pixel_type_ == pixel_type_t::FLOAT);
    std::vector<float> pixels(width_ * height_ * 4);
    _gl glReadBuffer(_gl GL_COLOR_ATTACHMENT0);
    _gl glReadPixels(0, 0, width_, height_, _gl GL_RGBA, _gl GL_FLOAT,
                     pixels.data());
    return pixels;
};