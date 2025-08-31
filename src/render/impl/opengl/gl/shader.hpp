#pragma once
#include <public.h>

#include <render/impl/opengl/core/typedef.hpp>
using namespace ::gl;
#define _GL ::gl::
namespace xcal::render::opengl::GL {
class Shader {
    friend class Object;
    friend class xcal::render::opengl::GL::ShaderProgram;

   private:
    _GL GLuint shader_ = 0;
    _GL GLenum type_;

   private:
    Shader(const Shader &) = delete;
    Shader(Shader &&o) { _STD swap(shader_, o.shader_); }
    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&o) {
        _STD swap(shader_, o.shader_);
        return *this;
    }

   public:
    Shader(_GL GLenum type) : type_(type) {};
    Shader(_GL GLenum type, _GL GLuint shader)
        : type_{type}, shader_(shader) {};
    ~Shader() { destroy(); };

   public:
    bool is_valid() { return shader_ != 0; };
    void swap(Shader &o) { _STD swap(shader_, o.shader_); }
    void destroy();
    static Shader from_source(_GL GLenum type, std::string_view source);
    static Shader from_file(_GL GLenum type, std::string_view file_path);
};
#undef _GL
}  // namespace xcal::render::opengl::GL