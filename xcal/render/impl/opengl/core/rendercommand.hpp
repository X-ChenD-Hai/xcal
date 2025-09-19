#include <cstddef>
#include <vector>
#include <xcal/render/impl/opengl/core/typedef.hpp>

namespace xcal::render::opengl::GL {
struct RenderCommand {
    gl::GLuint vao;
    std::vector<gl::GLuint> program;
    gl::GLenum mode;
    size_t count;
};
}  // namespace xcal::render::opengl::GL