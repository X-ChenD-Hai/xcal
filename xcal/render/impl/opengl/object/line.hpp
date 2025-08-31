#pragma once
#include <xcal/public.h>

#include <xcal/mobject/objects/line.hpp>
#include <xcal/render/impl/opengl/gl/buffer.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>

namespace xcal::render::opengl::object {
class Line : public xcal::render::opengl::object::Object {
   private:
    GL::Buffer vbo_;
    mobject::Line *mobject_{nullptr};
    std::shared_ptr<GL::ShaderProgram> shader_program_;
    static std::shared_ptr<GL::ShaderProgram> get_shader_program();

   public:
    explicit Line(mobject::Line *mobject);
    virtual void create() override;
    virtual void destroy() override;
    virtual void render() override;
    Line(const Line &) = delete;
};
}  // namespace xcal::render::opengl::object
XCAL_OPENGL_OBJECT_CREATER_HELPER(Line, mobject);