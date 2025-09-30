#pragma once
#include <format>
#include <string>
#include <xcal/mobject/core/composedmobject.hpp>
#include <xcal/render/utils/resourcedistributor.hpp>
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
    render::utils::DynamicResourceDistributor<GL::Buffer, GeometryVertexId>;

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
}  // namespace xcal::render::opengl::utils