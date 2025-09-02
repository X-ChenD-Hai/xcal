#include <xcal/render/impl/opengl/utils/openglapiloadhelper.inc>

//
#include <xcal/render/impl/opengl/gl/shader.hpp>
#include <xcal/render/impl/opengl/gl/shaderprogram.hpp>

#define ROLE GL
#define LABEL ShaderProgram
#include <xcal/utils/logmacrohelper.inc>

void xcal::render::opengl::GL::ShaderProgram::atttach_shader(
    const Shader &shader) {
    if (program_ == 0) {
        program_ = _gl glCreateProgram();
    }
    _I("Attaching shader: " << shader.shader_);
    _gl glAttachShader(program_, shader.shader_);
}
void xcal::render::opengl::GL::ShaderProgram::link() {
    if (program_ == 0) {
        throw std::runtime_error("program not created");
    }
    _gl glLinkProgram(program_);
    _gl GLint ok;
    _gl glGetProgramiv(program_, _gl GL_LINK_STATUS, &ok);
    if (!ok) {
        _gl GLint length;
        _gl glGetProgramiv(program_, _gl GL_INFO_LOG_LENGTH, &length);
        std::string log(length, '\0');
        _gl glGetProgramInfoLog(program_, length, nullptr, log.data());
        _E("Failed to link program: " << program_ << " " << log);
        throw std::runtime_error(log);
    }
    _I("Program linked: " << program_);
};
void xcal::render::opengl::GL::ShaderProgram::use() const {
    if (program_ == 0) {
        throw std::runtime_error("program not created");
    }
    _gl glUseProgram(program_);
};
;
void xcal::render::opengl::GL::ShaderProgram::destroy() {
    if (program_ != 0) {
        _gl glDeleteProgram(program_);
        _I("Program deleted: " << program_);
    }
    program_ = 0;
};

xcal::render::opengl::GL::ShaderProgram::ShaderProgram() {};
void xcal::render::opengl::GL::ShaderProgram::uniform(
    const char *name, const xcmath::mat<gl::GLfloat, 4, 4> &mat) const {
    _gl glUniformMatrix4fv(_gl glGetUniformLocation(program_, name), 1,
                           _gl GL_TRUE, &mat[0][0]);
}
void xcal::render::opengl::GL::ShaderProgram::uniform(
    const char *name, const xcmath::mat<gl::GLfloat, 3, 3> &mat) const {
    _gl glUniformMatrix3fv(_gl glGetUniformLocation(program_, name), 1,
                           _gl GL_TRUE, &mat[0][0]);
}
std::shared_ptr<xcal::render::opengl::GL::ShaderProgram>
xcal::render::opengl::GL::ShaderProgram::from_file(
    std::string_view vertex_file, std::string_view fragment_file) {
    auto tmp = std::make_shared<xcal::render::opengl::GL::ShaderProgram>();
    tmp->atttach_shader(xcal::render::opengl::GL::Shader::from_file(
        _gl GL_VERTEX_SHADER, vertex_file));
    tmp->atttach_shader(xcal::render::opengl::GL::Shader::from_file(
        _gl GL_FRAGMENT_SHADER, fragment_file));
    tmp->link();
    tmp->use();
    _D("Shader program created: " << tmp.get());
    return tmp;
}
