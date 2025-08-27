#pragma once
#include <mobject/objects/line.hpp>
#include <render/impl/opengl/object/object.hpp>
namespace xcal::render::opengl::object {
class Line : public xcal::render::opengl::object::Object {
   private:
    mobject::Line *mobject_{nullptr};

   public:
    Line(mobject::Line *mobject);
    virtual void create() override;
    virtual void destroy() override;
    virtual void render() override;
    Line(const Line &) = delete;
    Line &operator=(const Line &) = default;
    Line &operator=(Line &&) = default;
};
}  // namespace xcal::render::opengl::object
XCAL_OPENGL_OBJECT_CREATER_HELPER(Line, mobject);