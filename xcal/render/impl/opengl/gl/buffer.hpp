#pragma once
#include <xcal/public.h>

#include <xcal/render/impl/opengl/core/typedef.hpp>
namespace xcal::render::opengl::GL {

class XCAL_API Buffer {
    friend class Object;

   private:
    gl::GLuint vbo_ = 0;
    gl::GLuint size_ = 0;
    gl::GLenum target_{};

   private:
    Buffer(const Buffer &) = delete;
    Buffer(Buffer &&o) { swap(o); }

    Buffer &operator=(const Buffer &) = delete;
    Buffer &operator=(Buffer &&o) {
        swap(o);
        return *this;
    }

   public:
    Buffer(gl::GLenum target);
    ~Buffer();

   public:
    bool is_valid() const { return vbo_ != 0; };
    void bind_as(gl::GLenum target) const;
    void bind() const;
    void get_buffer_data(std::vector<char> &data) const;
    void get_buffer_data(std::vector<char> &data, gl::GLenum target) const;

   public:
    void swap(Buffer &o) {
        std::swap(vbo_, o.vbo_);
        std::swap(size_, o.size_);
    }
    void buffer_data(const void *data, gl::GLuint size, gl::GLenum usage);
    template <typename T>
    void buffer_data(const std::vector<T> &data, gl::GLenum usage) {
        buffer_data(data.data(), data.size() * sizeof(T), usage);
    }
    void destroy();
};
}  // namespace xcal::render::opengl::GL