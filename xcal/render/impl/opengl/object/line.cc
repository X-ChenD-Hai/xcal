#include <glad/glad.h>
//
#include <xcal/render/impl/opengl/gl/shader.hpp>
#include <xcal/render/impl/opengl/gl/shaderprogram.hpp>
#include <xcal/render/impl/opengl/object/line.hpp>

#define ROLE OpenGLObject
#define LABEL Line
#include <xcal/utils/logmacrohelper.inc>
void xcal::render::opengl::object::Line::create() {
    _I("Create Line: " << mobject_);
    vao().bind();
    vbo_.bind();
    std::array<float, 6> vertices = {
        mobject_->start().x(), mobject_->start().y(), 0,
        mobject_->end().x(),   mobject_->end().y(),   0};
    vbo_.buffer_data(vertices.data(), vertices.size() * sizeof(float),
                     GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
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
