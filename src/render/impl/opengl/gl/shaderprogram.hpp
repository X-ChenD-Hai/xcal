#pragma once
#include <public.h>

#include <render/impl/opengl/core/typedef.hpp>
using namespace gl;
namespace xcal::render::opengl::GL {

class ShaderProgram {
    friend class Object;

   private:
    GLuint program_{};

   private:
    ShaderProgram(const ShaderProgram &) = delete;
    ShaderProgram(ShaderProgram &&o) { _STD swap(program_, o.program_); }
    ShaderProgram &operator=(const ShaderProgram &) = delete;
    ShaderProgram &operator=(ShaderProgram &&o) {
        _STD swap(program_, o.program_);
        return *this;
    }

   public:
    ShaderProgram();
    ~ShaderProgram() { destroy(); };

   public:
    bool is_valid() { return program_ != 0; };
    void swap(ShaderProgram &o) { _STD swap(program_, o.program_); }
    void atttach_shader(const Shader &shader);
    void link();
    void use();
    void destroy();
};
}  // namespace xcal::render::opengl::GL