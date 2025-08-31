#include <render/impl/opengl/utils/glbindingincludehelper.inc>
//
#include <render/impl/opengl/gl/shader.hpp>
#include <render/impl/opengl/gl/shaderprogram.hpp>

#define ROLE GL
#define LABEL ShaderProgram
#include <utils/logmacrohelper.inc>

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
    GLint ok;
    _gl glGetProgramiv(program_, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint length;
        _gl glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &length);
        std::string log(length, '\0');
        _gl glGetProgramInfoLog(program_, length, nullptr, log.data());
        _E("Failed to link program: " << program_ << " " << log);
        throw std::runtime_error(log);
    }
    _I("Program linked: " << program_);
};
void xcal::render::opengl::GL::ShaderProgram::use() {
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