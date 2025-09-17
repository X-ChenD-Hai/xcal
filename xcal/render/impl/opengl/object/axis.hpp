#pragma once
#include <xcal/public.h>

#include <xcal/mobject/objects/axis.hpp>
#include <xcal/render/impl/opengl/gl/buffer.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>
#include <xcal/render/impl/opengl/utils/singlemobjectwrapper.hpp>
#include <xcmath/mobject/mat.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::render::opengl::object {
class XCAL_API Axis : public Object {
   public:
    using mat = xcmath::mat<float_t, 4, 4>;

   private:
    GL::Buffer vbo_;
    utils::SingleMObjectWrapper<mobject::Axis> mobject_{nullptr};
    std::shared_ptr<GL::ShaderProgram> shader_program_;

   public:
    explicit Axis(mobject::Axis *mobject);
    virtual void create() override;
    virtual void destroy() override;
    virtual void render() const override;
    virtual void update_projection_view(
        const xcmath::mat4<float_t> &projection_view) override;

    Axis(const Axis &) = delete;
};
}  // namespace xcal::render::opengl::object
XCAL_OPENGL_REGIST_OBJECT(xcal::render::opengl::object::Axis, Axis);
