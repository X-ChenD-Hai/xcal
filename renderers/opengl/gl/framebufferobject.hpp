#include XCAL_OPENGL_RENDERER_CONFIG_HEADER

#include <core/typedef.hpp>
#include <gl/texture.hpp>
#include <vector>
namespace xcal::render::opengl::GL {
class FramebufferObject {
   public:
    using color_format_t = Texture::color_format_t;
    using pixel_type_t = Texture::pixel_type_t;

   private:
    gl::GLuint fbo_{0};
    Texture texture_;
    gl::GLuint width_{};
    gl::GLuint height_{};
    color_format_t color_format_{color_format_t::RGBA};
    pixel_type_t pixel_type_{pixel_type_t::UNSIGNED_BYTE};

   public:
    FramebufferObject(gl::GLuint width, gl::GLuint height,
                      color_format_t color_format = color_format_t::RGBA,
                      pixel_type_t pixel_type = pixel_type_t::UNSIGNED_BYTE);
    ~FramebufferObject();

   public:
    bool_t is_valid() const { return fbo_ != 0; }
    gl::GLuint width() const { return width_; }
    gl::GLuint height() const { return height_; }
    const Texture &texture() const { return texture_; }
    void bind() const;
    void swap(FramebufferObject &o) {
        std::swap(fbo_, o.fbo_);
        texture_.swap(o.texture_);
        std::swap(width_, o.width_);
        std::swap(height_, o.height_);
        std::swap(color_format_, o.color_format_);
        std::swap(pixel_type_, o.pixel_type_);
    }
    std::vector<char> read_pixels_char() const;
    std::vector<float> read_pixels_float() const;
    static void unbind();
};
}  // namespace xcal::render::opengl::GL