#ifdef GL_BACKEND_GLBINDING
#include <glbinding/gl/gl.h>
#ifndef __gl_h_
#define __gl_h_
#endif  //  __gl_h_
#define _gl ::gl::
#elif defined(GL_BACKEND_GLAD)
#include <glad/glad.h>
#define _gl
#else
#error "No OpenGL backend defined"
#endif  // GL_BACKEND_GLBINDING