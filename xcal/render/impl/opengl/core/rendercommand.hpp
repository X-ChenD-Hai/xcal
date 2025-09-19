#include <cstddef>
#include <vector>
#include <xcal/render/impl/opengl/core/typedef.hpp>
#include <xcal/render/impl/opengl/utils/resourcedistributor.hpp>


namespace xcal::render::opengl::GL {
class GLObject {
   public:
    void vao(size_t id);
    void push_vbo(size_t id);
    void vbo(size_t id);
    void push_ebo(size_t id);
    void ebo(size_t id);
};

struct RenderCommand {
    gl::GLuint vao;
    std::vector<gl::GLuint> program;
    gl::GLenum mode;
    size_t count;
};
}  // namespace xcal::render::opengl::GL