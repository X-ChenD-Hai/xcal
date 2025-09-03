#pragma once
#include <xcal/mobject/core/mobject.hpp>
#include <xcal/mobject/mobject.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::render::opengl::utils {
class SingleMObjectWrapperImpl {
    template <class T>
        requires(std::is_base_of_v<mobject::MObject, T>)
    friend class SingleMObjectWrapper;

   public:
    using mat = xcmath::mat<float_t, 4, 4>;

   private:
    mobject::MObject* mobject_{nullptr};
    mutable mat model_matrox_cache_ = mat::eye();

   public:
    SingleMObjectWrapperImpl(mobject::MObject* mobject) : mobject_(mobject) {};
    ~SingleMObjectWrapperImpl() {};
    void set_mobject(mobject::MObject* mobject);
    mobject::MObject* mobject() const { return mobject_; }
    bool model_matrix_should_update() const;
    void update_model_matrix() const;
    mat& model_matrix() const;
};
template <class T>
    requires(std::is_base_of_v<mobject::MObject, T>)
class SingleMObjectWrapper : public SingleMObjectWrapperImpl {
   public:
    using SingleMObjectWrapperImpl::mat;
    using SingleMObjectWrapperImpl::SingleMObjectWrapperImpl;
    T* mobject() const { return (T*)mobject_; }
    T* operator->() const { return (T*)mobject_; }  // operator ->()
};
}  // namespace xcal::render::opengl::utils