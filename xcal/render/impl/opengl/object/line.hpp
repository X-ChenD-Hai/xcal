#pragma once
#include <xcal/public.h>

#include <xcal/mobject/objects/line.hpp>
#include <xcal/render/impl/opengl/gl/buffer.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>
#include <xcal/render/impl/opengl/utils/singlemobjectwrapper.hpp>
#include <xcmath/mobject/mat.hpp>
#include <xcmath/xcmath.hpp>
class StaticLine;
namespace xcal::render::opengl::object {
class XCAL_API Line : public Object {
   public:
    using mat = xcmath::mat<float_t, 4, 4>;

   private:
   mutable struct {
        xcmath::vec4<float_t> direction;
        xcmath::vec4<float_t> color;
        xcmath::mat4<float_t> model;
    } ubo_data_;
    mutable GL::Buffer ubo_;
    std::shared_ptr<StaticLine> static_line_;
    utils::SingleComposedMObjectWrapper<mobject::Line> mobject_{nullptr};

   public:
    explicit Line(mobject::Line *mobject);
    void create() override;
    void destroy() override;
    void render() const override;
    void update_ubo_data() const;
    void update_projection_view(
        const xcmath::mat4<float_t> &view_projection) override;

    Line(const Line &) = delete;
};
}  // namespace xcal::render::opengl::object
XCAL_OPENGL_REGIST_OBJECT(xcal::render::opengl::object::Line, Line);
