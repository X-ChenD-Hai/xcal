#include <xcal/render/impl/opengl/gl/shaderprogram.hpp>

namespace xcal::render::opengl::utils {
template <class T, size_t _id>
std::shared_ptr<xcal::render::opengl::GL::ShaderProgram> create_shader() {
    static_assert(false, "Not implemented");
};
template <class T, size_t _id>
class ShaderInstance {
   private:
    static std::weak_ptr<xcal::render::opengl::GL::ShaderProgram> shader_;

   public:
    static std::shared_ptr<xcal::render::opengl::GL::ShaderProgram> instance() {
        if (shader_.expired()) {
            auto tmp = create_shader<T, _id>();
            shader_ = tmp;
            return tmp;
        }
        return shader_.lock();
    }
};
template <class T, size_t _id>
std::weak_ptr<xcal::render::opengl::GL::ShaderProgram>
    ShaderInstance<T, _id>::shader_{};
}  // namespace xcal::render::opengl::utils

#define XCAL_SHADER_INSTANCE(T, _id)                         \
    template <>                                              \
    std::shared_ptr<xcal::render::opengl::GL::ShaderProgram> \
    xcal::render::opengl::utils::create_shader<T, _id>()
