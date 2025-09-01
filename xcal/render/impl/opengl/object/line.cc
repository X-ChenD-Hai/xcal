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
#include <xcal/utils/logmacrohelper.inc>
#include <xcmath/utils/show.hpp>

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

    shader_program_ = get_shader_program();
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

XCAL_OPENGL_OBJECT_CREATER_HELPER(Line, mobject) {
    return std::make_unique<xcal::render::opengl::object::Line>(mobject);
}
std::shared_ptr<xcal::render::opengl::GL::ShaderProgram>
xcal::render::opengl::object::Line::get_shader_program() {
    static std::weak_ptr<GL::ShaderProgram> static_program;
    if (static_program.use_count() == 0) {
        auto tmp = std::make_shared<xcal::render::opengl::GL::ShaderProgram>();
        static_program = tmp;
        tmp->atttach_shader(xcal::render::opengl::GL::Shader::from_file(
            _gl GL_VERTEX_SHADER, "res/line.vs"));
        tmp->atttach_shader(xcal::render::opengl::GL::Shader::from_file(
            _gl GL_FRAGMENT_SHADER, "res/line.fs"));
        tmp->link();
        tmp->use();
        _D("Shader program created: " << tmp.get());
        return tmp;
    }
    return static_program.lock();
}