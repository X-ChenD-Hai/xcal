#include <glbinding/gl/gl.h>
#ifndef __gl_h_
#define __gl_h_
#endif  //
#include <render/impl/opengl/gl/shader.hpp>
#include <render/impl/opengl/gl/shaderprogram.hpp>
#include <render/impl/opengl/object/line.hpp>
using namespace ::gl;  //

#define ROLE OpenGLObject
#define LABEL Line
#include <utils/logmacrohelper.inc>
void xcal::render::opengl::object::Line::create() {
    _I("Create Line: " << mobject_);
    vao().bind();
    vbo_.bind();
    std::array<float, 12> vertices = {
        mobject_->start().x(),
        mobject_->start().y(),
        0,  //
        mobject_->stroke_color().r(),
        mobject_->stroke_color().g(),
        mobject_->stroke_color().b(),  //
        mobject_->end().x(),
        mobject_->end().y(),
        0,  //
        mobject_->stroke_color().r(),
        mobject_->stroke_color().g(),
        mobject_->stroke_color().b(),  //
    };
    vbo_.buffer_data(vertices.data(), vertices.size() * sizeof(float),
                     GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float),            // stride
                          (void*)(0 * sizeof(float)));  // offset

    // 颜色属性：location 1，每个顶点 3 个 float，offset 3*float
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float),            // stride
                          (void*)(3 * sizeof(float)));  // offset
    shader_program_ = get_shader_program();
    _D("Line created: " << this << " from mobject: " << mobject_);
};
void xcal::render::opengl::object::Line::destroy() {
    _I("Destroy Line: " << this);
    shader_program_.reset();
    vbo_.destroy();
};
void xcal::render::opengl::object::Line::render() {
    vao().bind();
    shader_program_->use();
    glDrawArrays(GL_LINES, 0, 2);
};
xcal::render::opengl::object::Line::Line(mobject::Line* mobject)
    : mobject_(mobject), vbo_(GL_ARRAY_BUFFER) {
    _I("Create Line: " << this << " from mobject: " << mobject_);
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
            GL_VERTEX_SHADER, "res/line.vs"));
        tmp->atttach_shader(xcal::render::opengl::GL::Shader::from_file(
            GL_FRAGMENT_SHADER, "res/line.fs"));
        tmp->link();
        tmp->use();
        _D("Shader program created: " << tmp.get());
        return tmp;
    }
    return static_program.lock();
}
