#pragma once
#include XCAL_OPENGL_RENDERER_CONFIG_HEADER

#include <gl/buffer.hpp>
#include <object/object.hpp>
#include <utils/singlemobjectwrapper.hpp>
#include <xcal/mobject/objects/axis.hpp>
#include <xcmath/mobject/mat.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::render::opengl::object {
class XCAL_OPENGL_RENDERER_API Axis3D : public Object {
   public:
    using mat = xcmath::mat<float_t, 4, 4>;

   private:
    GL::Buffer vbo_;
    utils::SingleMGroupWrapper<mobject::Axis3D> mobject_{nullptr};
    std::shared_ptr<GL::ShaderProgram> shader_program_;

   public:
    explicit Axis3D(mobject::Axis3D *mobject);
    void create() override;
    void destroy() override;
    void render() const override;
    void update_projection_view(
        const xcmath::mat4<float_t> &projection_view) override;

    Axis3D(const Axis3D &) = delete;
};
}  // namespace xcal::render::opengl::object
XCAL_OPENGL_REGIST_OBJECT(xcal::render::opengl::object::Axis3D, Axis3D);
