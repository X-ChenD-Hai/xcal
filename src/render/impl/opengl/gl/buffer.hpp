#include <public.h>

#include <render/impl/opengl/core/typedef.hpp>
namespace xcal::render::opengl::GL {

class Buffer {
    friend class Object;

   private:
    GLuint vbo_ = 0;
    GLuint size_ = 0;
    GLenum target_ = 0;

   private:
    Buffer(const Buffer &) = delete;
    Buffer(Buffer &&o) { swap(o); }

    Buffer &operator=(const Buffer &) = delete;
    Buffer &operator=(Buffer &&o) {
        swap(o);
        return *this;
    }

   public:
    Buffer(GLenum target);
    ~Buffer();

   public:
    bool is_valid() { return vbo_ != 0; };
    void swap(Buffer &o) {
        std::swap(vbo_, o.vbo_);
        std::swap(size_, o.size_);
    }
    void bind_as(GLenum target);
    void bind();
    void buffer_data(const void *data, GLuint size, GLenum usage);
    template <typename T>
    void buffer_data(const std::vector<T> &data, GLenum usage) {
        buffer_data(data.data(), data.size() * sizeof(T), usage);
    }
    void get_buffer_data(std::vector<char> &data);
    void get_buffer_data(std::vector<char> &data, GLenum target);
    void destroy();
};
}  // namespace xcal::render::opengl::GL