#include "xcal/mobject/objects/line.hpp"

#include <xcal/render/impl/opengl/utils/glbindingincludehelper.inc>

//
#include <xcal/render/impl/opengl/gl/shader.hpp>
#include <xcal/render/impl/opengl/gl/shaderprogram.hpp>
#include <xcal/render/impl/opengl/object/line.hpp>
#include <xcmath/xcmath.hpp>

#include "xcal/public.h"
#include "xcal/render/impl/opengl/object/object.hpp"
#define XCAL_OUT_TO_STDERR
#define ROLE OpenGLObject
#define LABEL Line
#include <xcal/render/impl/opengl/utils/shaderinstence.hpp>
#include <xcal/utils/logmacrohelper.inc>
#include <xcmath/utils/show.hpp>
#define SHADER_ID 0
XCAL_SHADER_INSTANCE(xcal::render::opengl::object::Line, SHADER_ID) {
    return GL::ShaderProgram::from_file("res/line.vs", "res/line.fs");
}

void xcal::render::opengl::object::Line::create() {
    vao().bind();
    vbo_.bind();
    const xcmath::vec2<float_t> direct = mobject_->direct().value() / 2;
    _D("Create Line: " << mobject_.mobject() << " with direct: " << direct);
    std::array<_gl GLfloat, 12> vertices = {
        -direct.x(),
        -direct.y(),
        0,  //
        mobject_->stroke_color().r(),
        mobject_->stroke_color().g(),
        mobject_->stroke_color().b(),  //
        direct.x(),
        direct.y(),
        0,  //
        mobject_->stroke_color().r(),
        mobject_->stroke_color().g(),
        mobject_->stroke_color().b(),  //
    };
    vbo_.buffer_data(vertices.data(), vertices.size() * sizeof(float),
                     _gl GL_STATIC_DRAW);
    _gl glEnableVertexAttribArray(0);
    _gl glVertexAttribPointer(0, 3, _gl GL_FLOAT, _gl GL_FALSE,
                              6 * sizeof(float),            // stride
                              (void*)(0 * sizeof(float)));  // offset

    // 颜色属性：location 1，每个顶点 3 个 float，offset 3*float
    _gl glEnableVertexAttribArray(1);
    _gl glVertexAttribPointer(1, 3, _gl GL_FLOAT, _gl GL_FALSE,
                              6 * sizeof(float),            // stride
                              (void*)(3 * sizeof(float)));  // offset

    shader_program_ = utils::ShaderInstance<Line, SHADER_ID>::instance();
};
void xcal::render::opengl::object::Line::destroy() {
    _I("Destroy Line: " << this);
    shader_program_.reset();
    vbo_.destroy();
};
void xcal::render::opengl::object::Line::render() const {
    vao().bind();
    shader_program_->use();
    shader_program_->uniform("model", mobject_.model_materix());
    _gl glDrawArrays(_gl GL_LINES, 0, 2);
};
xcal::render::opengl::object::Line::Line(mobject::Line* mobject)
    : mobject_(mobject), vbo_(_gl GL_ARRAY_BUFFER) {
    _I("Create Line: " << this << " from mobject: " << mobject_.mobject());
};

XCAL_OPENGL_REGIST_OBJECT_IMPL(xcal::render::opengl::object::Line, Line)