#pragma once
#include <xcal/mobject/core/abs_mgroup.hpp>
#include <xcal/mobject/mobject.hpp>
#include <xcal/render/impl/opengl/object/object.hpp>
#include <xcmath/xcmath.hpp>

namespace xcal::render::opengl::utils {
template <class T>
    requires(std::is_base_of_v<mobject::AbsMObject, T> &&
             std::is_base_of_v<mobject::PositionableMObject<T>, T> &&
             std::is_base_of_v<mobject::ScalableMObject<T>, T> &&
             std::is_base_of_v<mobject::RotatableMObject<T>, T>)
class XCAL_API SingleComposedMObjectWrapper {
   public:
    using mat = xcmath::mat<float_t, 4, 4>;

   protected:
    T* mobject_{nullptr};
    mutable mat model_matrox_cache_ = mat::eye();

   public:
    explicit SingleComposedMObjectWrapper(T* mobject) : mobject_(mobject) {};
    ~SingleComposedMObjectWrapper() = default;
    void set_mobject(T* mobject) { mobject_ = mobject; }
    bool model_matrix_should_update() const {
        return mobject_->pos().is_changed() ||
               mobject_->rotation().is_changed() ||
               mobject_->scale().is_changed();
    }
    void update_model_matrix() const {
        model_matrox_cache_ = xcmath::translate(
            xcmath::rotate(
                xcmath::scale(xcmath::mat4<float_t>::eye(),
                              {mobject_->scale_x(), mobject_->scale_y(), 1.0f}),
                mobject_->rotation().value().z(), {0.0f, 0.0f, 1.0f}),
            {mobject_->pos().value().x(), mobject_->pos().value().y(), 0.0f});
        mobject_->pos().reset_changed();
        mobject_->rotation().reset_changed();
        mobject_->scale().reset_changed();
    }
    mat& model_matrix() const {
        if (model_matrix_should_update()) {
            update_model_matrix();
        }
        return model_matrox_cache_;
    }
    T* mobject() const { return (T*)mobject_; }
    T* operator->() const { return (T*)mobject_; }  // operator ->()
};
template <class T>
class XCAL_API SingleMGroupWrapper
    : public SingleComposedMObjectWrapper<xcal::mobject::AbsMGroup> {
   public:
    using SingleComposedMObjectWrapper<xcal::mobject::AbsMGroup>::mat;
    using SingleComposedMObjectWrapper<
        xcal::mobject::AbsMGroup>::SingleComposedMObjectWrapper;
    xcal::mobject::AbsMGroup* mobject() const {
        return (xcal::mobject::AbsMGroup*)mobject_;
    }
    T* operator->() const {
        return (T*)mobject_;  // operator ->()
    }
};

}  // namespace xcal::render::opengl::utils