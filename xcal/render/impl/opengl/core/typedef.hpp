#pragma once
#if defined(GL_BACKEND_GLBINDING) && defined(GL_BACKEND_GLAD)
#error "Cannot define both GL_BACKEND_GLBINDING and GL_BACKEND_GLAD"
#endif

typedef struct GLFWwindow GLFWwindow;
namespace gl {
#ifdef GL_BACKEND_GLBINDING
enum class GLenum : unsigned int;
#elif defined(GL_BACKEND_GLAD)
typedef unsigned char GLboolean;
typedef unsigned int GLenum;
#endif
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

#ifdef GL_BACKEND_GLBINDING
namespace glbinding {
class GLboolean;
};
#elif defined(GL_BACKEND_GLAD)
#endif

namespace xcal::render::opengl::object {
class Object;
}
namespace xcal::render::opengl::GL {
class Shader;
class ShaderProgram;
class VertexArrayObject;
class Buffer;
}  // namespace xcal::render::opengl::GL