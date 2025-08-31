#include <glad/glad.h>
//
#include <fstream>
#include <xcal/render/impl/opengl/gl/shader.hpp>

#define ROLE GL
#define LABEL Shader
#include <xcal/utils/logmacrohelper.inc>

xcal::render::opengl::GL::Shader xcal::render::opengl::GL::Shader::from_source(
    GLenum type, std::string_view source) {
    GLuint shader = glCreateShader(type);
    const char *src = source.data();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        std::string log(length, '\0');
        glGetShaderInfoLog(shader, length, nullptr, log.data());
        _E("Failed to compile shader: " << log);
        throw std::runtime_error(log);
    }
    return Shader(type, shader);
}
xcal::render::opengl::GL::Shader xcal::render::opengl::GL::Shader::from_file(
    GLenum type, std::string_view file_path) {
    _I("Loading shader from file: " << file_path);
    std::ifstream file(file_path.data());
    if (!file.is_open()) {
        throw std::runtime_error(_STD string("Failed to open file: ") +
                                 _STD string(file_path.data()));
    }
    std::string source((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    file.close();
    _I("Shader source: " << source);
    return from_source(type, source);
}
void xcal::render::opengl::GL::Shader::destroy() {
    if (shader_ != 0) {
        glDeleteShader(shader_);
        _I("Shader deleted: " << shader_);
    }
    shader_ = 0;
};