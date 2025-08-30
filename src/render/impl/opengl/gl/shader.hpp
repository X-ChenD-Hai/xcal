#pragma once
#include <public.h>

#include <render/impl/opengl/core/typedef.hpp>
namespace xcal::render::opengl::GL {
class Shader {
    friend class Object;
    friend class xcal::render::opengl::GL::ShaderProgram;

   private:
    GLuint shader_ = 0;
    GLenum type_ = 0;

   private:
    Shader(const Shader &) = delete;
    Shader(Shader &&o) { _STD swap(shader_, o.shader_); }
    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&o) {
        _STD swap(shader_, o.shader_);
        return *this;
    }

   public:
    Shader(GLenum type) : type_(type) {};
    Shader(GLenum type, GLuint shader) : type_{type}, shader_(shader) {};
    ~Shader() { destroy(); };

   public:
    bool is_valid() { return shader_ != 0; };
    void swap(Shader &o) { _STD swap(shader_, o.shader_); }
    void destroy();
    static Shader from_source(GLenum type, std::string_view source);
    static Shader from_file(GLenum type, std::string_view file_path);
};
}  // namespace xcal::render::opengl::GL