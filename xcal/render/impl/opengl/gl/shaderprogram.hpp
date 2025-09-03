#pragma once
#include <xcal/public.h>

#include <memory>
#include <string_view>
#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcmath/xcmath.hpp>
namespace xcal::render::opengl::GL {
class XCAL_API ShaderProgram {
    friend class Object;

   private:
    gl::GLuint program_{};

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
   public:
    bool is_valid() const { return program_ != 0; };
    void atttach_shader(const Shader &shader);
    void use() const;
    void uniform(const char *name,
                 const xcmath::mat<gl::GLfloat, 4, 4> &mat) const;
    void uniform(const char *name,
                 const xcmath::mat<gl::GLfloat, 3, 3> &mat) const;

   public:
    static std::shared_ptr<ShaderProgram> from_file(
        std::string_view vertex_file, std::string_view fragment_file);

   public:
    void swap(ShaderProgram &o) { _STD swap(program_, o.program_); }
    void link();
    void destroy();
};
}  // namespace xcal::render::opengl::GL