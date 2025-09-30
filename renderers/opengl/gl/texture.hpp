#include XCAL_OPENGL_RENDERER_CONFIG_HEADER

#include <core/typedef.hpp>

namespace xcal::render::opengl::GL {
class FramebufferObject;
class Texture {
    friend class ::xcal::render::opengl::GL::FramebufferObject;

   public:
    enum class color_format_t {
        RGB,
        RGBA,
        DEPTH,
        STENCIL,
    };
    enum class pixel_type_t {
        UNSIGNED_BYTE,
        FLOAT,
    };

   private:
    gl::GLuint texture_ = 0;
    gl::GLenum target_{};

   public:
    Texture(const Texture &) = delete;
    Texture(Texture &&o) { swap(o); }
    Texture &operator=(const Texture &) = delete;
    Texture &operator=(Texture &&o) {
        swap(o);
        return *this;
    }
    Texture(gl::GLenum target);
    ~Texture();
    bool_t is_valid() const { return texture_ != 0; }
    void image_2d(gl::GLint level, color_format_t internalformat,
                  gl::GLsizei width, gl::GLsizei height, gl::GLint border,
                  color_format_t format, pixel_type_t type,
                  const void *data) const;
    void parameteri(gl::GLenum pname, gl::GLenum param) const;
    void bind(gl::GLenum target) const;
    void bind() const;
    void unbind();
    void swap(Texture &o);
    static void unbind(gl::GLenum target);
    static gl::GLenum to_gl_enum(color_format_t format);
    static gl::GLenum to_gl_enum(pixel_type_t type);
};
}  // namespace xcal::render::opengl::GL