#pragma once
#include <format>
#include <string>
#include <xcal/mobject/core/composedmobject.hpp>
#include <xcal/render/impl/opengl/utils/resourcedistributor.hpp>
namespace xcal::render::opengl::GL {
class Buffer;
struct DynamicResourceId;
}  // namespace xcal::render::opengl::GL
namespace xcal::render::opengl::utils {

struct GeometryVertexId {
    using type = std::string;

    template <mobject::is_mobject MObject, size_t Id = 0, typename... Args>
    static type allocate(Args&&... args) {
        return std::format("{}_{}{}", MObject::META_INFO::type_name, Id,
                           (std::format("_{}", args) + ...));
    }
};

using GeometryVertexDistributor =
    DynamicResourceDistributor<GL::Buffer, GeometryVertexId>;

// id = mobject_id_args

#define XCAL_GEOMETRY_VERTEX_INSTANCE(MObject, Id, args...)                \
    template <>                                                            \
    struct xcal::render::opengl::utils::DynamicResourceAllocator<          \
        xcal::render::opengl::GL::Buffer, std::string, MObject, Id> {      \
        static std::shared_ptr<xcal::render::opengl::GL::Buffer> allocate( \
            args);                                                         \
    };                                                                     \
    std::shared_ptr<xcal::render::opengl::GL::Buffer>                      \
    xcal::render::opengl::utils::DynamicResourceAllocator<                 \
        xcal::render::opengl::GL::Buffer, std::string, MObject,            \
        Id>::allocate(args)
// class GeometryVertexDistributor {
//    private:
//     static std::unordered_map<std::string,
//                               std::weak_ptr<xcal::render::opengl::GL::Buffer>>
//         buffers_;

//    public:
//     using buffer_ptr_t = std::shared_ptr<xcal::render::opengl::GL::Buffer>;

//    public:
//     template <typename T>
//     static std::string prefix() {
//         return std::string(T::META_INFO::type_name) + "_";
//     }

//    public:
//     template <typename T>
//     static buffer_ptr_t buffer(std::string_view ident) {
//         auto key = prefix<T>() + std::string(ident);
//         auto it = buffers_.find(key);
//         if (it != buffers_.end()) {
//             return it->second.lock();
//         }
//         return nullptr;
//     }
//     template <typename T>
//     static void set_buffer(std::string_view ident, buffer_ptr_t buffer) {
//         auto key = prefix<T>() + std::string(ident);
//         buffers_[key] = buffer;
//     }
// };
}  // namespace xcal::render::opengl::utils