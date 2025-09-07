
#include <xcal/render/impl/opengl/gl/texture.hpp>
#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>

void xcal::render::opengl::GL::Texture::bind(gl::GLenum target) const {
    _gl glBindTexture(target, texture_);
};
void xcal::render::opengl::GL::Texture::unbind(gl::GLenum target) {
    _gl glBindTexture(target, 0);
};

void xcal::render::opengl::GL::Texture::parameteri(gl::GLenum pname,
                                                   gl::GLenum param) const {
    _gl glTexParameteri(target_, pname, param);
}
void xcal::render::opengl::GL::Texture::bind() const {
    _gl glBindTexture(target_, texture_);
};
void xcal::render::opengl::GL::Texture::unbind() {
    _gl glBindTexture(target_, 0);
};
gl::GLenum xcal::render::opengl::GL::Texture::to_gl_enum(
    color_format_t format) {
    static const gl::GLenum mapping[] = {
        _gl GL_RGB, _gl GL_RGBA, _gl GL_DEPTH_COMPONENT, _gl GL_STENCIL_INDEX};
    return mapping[static_cast<std::size_t>(format)];
}
xcal::render::opengl::GL::Texture::Texture(gl::GLenum target)
    : target_(target) {
    _gl glGenTextures(1, &texture_);
};
xcal::render::opengl::GL::Texture::~Texture() {
    if (is_valid()) _gl glDeleteTextures(1, &texture_);
    texture_ = 0;
};
void xcal::render::opengl::GL::Texture::swap(Texture &o) {
    std::swap(texture_, o.texture_);
    std::swap(target_, o.target_);
}
gl::GLenum xcal::render::opengl::GL::Texture::to_gl_enum(pixel_type_t type) {
    static const gl::GLenum mapping[] = {_gl GL_UNSIGNED_BYTE, _gl GL_FLOAT};
    return mapping[static_cast<std::size_t>(type)];
}
void xcal::render::opengl::GL::Texture::image_2d(
    gl::GLint level, color_format_t internalformat, gl::GLsizei width,
    gl::GLsizei height, gl::GLint border, color_format_t format,
    pixel_type_t type, const void *data) const {
    _gl glTexImage2D(target_, level, to_gl_enum(internalformat), width, height,
                     border, to_gl_enum(format), to_gl_enum(type), data);
};