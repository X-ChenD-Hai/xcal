#pragma once

#include <gl/buffer.hpp>
#include <object/object.hpp>
#include <utils/singlemobjectwrapper.hpp>
#include <xcal/mobject/objects/path.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::render::opengl::object {
class XCAL_OPENGL_RENDERER_API Path : public Object {
   public:
    using mat = xcmath::mat<float_t, 4, 4>;

   private:
    GL::Buffer stroke_vbo_;
    GL::Buffer fill_vbo_;
    GL::Buffer position_vbo_;
    utils::SingleComposedMObjectWrapper<mobject::Path> mobject_{nullptr};
    std::shared_ptr<GL::ShaderProgram> stroke_shader_program_;
    std::shared_ptr<GL::ShaderProgram> fill_shader_program_;

   public:
    explicit Path(mobject::Path *mobject);
    void create() override;
    void destroy() override;
    void render() const override;
    virtual void update_projection_view(
        const xcmath::mat4<float_t> &projection_view) override;

    Path(const Path &) = delete;
};
}  // namespace xcal::render::opengl::object
XCAL_OPENGL_REGIST_OBJECT(xcal::render::opengl::object::Path, Path);
