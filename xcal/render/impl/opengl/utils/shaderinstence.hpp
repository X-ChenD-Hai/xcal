#include <xcal/render/impl/opengl/gl/shaderprogram.hpp>
#include <xcal/render/impl/opengl/utils/resourcedistributor.hpp>
namespace xcal::render::opengl::utils {

template <typename Catgory, size_t Id>
struct ResourceAllocator<xcal::render::opengl::GL::ShaderProgram, Catgory, Id> {
    static std::shared_ptr<xcal::render::opengl::GL::ShaderProgram> allocate() {
        static_assert(false, "Not implemented");
    }
};
template <class T, size_t _id>
using ShaderInstance =
    StaticResourceDistributor<xcal::render::opengl::GL::ShaderProgram, T, _id>;

template <typename Catgory, size_t Id>
struct ResourceAllocator<xcal::render::opengl::GL::VertexArrayObject, Catgory,
                         Id> {
    static std::shared_ptr<xcal::render::opengl::GL::VertexArrayObject>
    allocate() {
        return std::make_shared<xcal::render::opengl::GL::VertexArrayObject>();
    }
};
template <class T, size_t _id>
using VertexArrayObjectInstance =
    StaticResourceDistributor<xcal::render::opengl::GL::VertexArrayObject, T,
                              _id>;

template <typename Catgory, size_t Id>
struct ResourceAllocator<xcal::render::opengl::GL::Buffer, Catgory, Id> {
    static std::shared_ptr<xcal::render::opengl::GL::Buffer> allocate() {
        return std::make_shared<xcal::render::opengl::GL::Buffer>();
    }
};
template <class T, size_t _id>
using BufferInstance =
    StaticResourceDistributor<xcal::render::opengl::GL::Buffer, T, _id>;

}  // namespace xcal::render::opengl::utils

#define XCAL_DEFINE_STATIC_GLOBJECT(T, Catgory, Id) \
    template <>                                     \
    std::shared_ptr<T>                              \
    xcal::render::opengl::utils::ResourceAllocator<T, Catgory, Id>::allocate()
#define XCAL_STATIC_GLOBJECT(T, Catgory, Id)                              \
    (::xcal::render::opengl::utils::StaticResourceDistributor<T, Catgory, \
                                                              Id>::instance())

#define XCAL_BUFFER_INSTANCE(T, _id)                  \
    template <>                                       \
    std::shared_ptr<xcal::render::opengl::GL::Buffer> \
    xcal::render::opengl::utils::ResourceAllocator<   \
        xcal::render::opengl::GL::Buffer, T, _id>::allocate()
#define XCAL_SHADER_INSTANCE(T, _id)                         \
    template <>                                              \
    std::shared_ptr<xcal::render::opengl::GL::ShaderProgram> \
    xcal::render::opengl::utils::ResourceAllocator<          \
        xcal::render::opengl::GL::ShaderProgram, T, _id>::allocate()

#ifdef XCAL_debug
#    define SHADER_FILE(name) (std::string(XCAL_OPENGL_SHADER_DIR) + (name))
#else
#    include <xcal/utils/paths.hpp>
#    define SHADER_FILE(name)                                                \
        (xcal::utils::paths::EXECUTABLE_DIR + "/" + XCAL_OPENGL_SHADER_DIR + \
         name)
#endif