#pragma once
typedef struct GLFWwindow GLFWwindow;
namespace glbinding {
class GLboolean;
};
namespace gl {
enum class GLenum : unsigned int;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
}  // namespace gl

namespace xcal::render::opengl::object {
class Object;
}
namespace xcal::render::opengl::GL {
class Shader;
class ShaderProgram;
class VertexArrayObject;
class Buffer;
}  // namespace xcal::render::opengl::GL