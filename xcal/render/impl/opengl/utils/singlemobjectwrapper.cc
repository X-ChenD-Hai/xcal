#include <xcal/render/impl/opengl/utils/singlemobjectwrapper.hpp>
#define XCAL_OUT_TO_STDERR
#define ROLE OpenGLObject
#define LABEL SingleObject
#include <xcal/utils/logmacrohelper.inc>
#include <xcmath/utils/show.hpp>

xcal::render::opengl::utils::SingleMObjectWrapperImpl::mat&
xcal::render::opengl::utils::SingleMObjectWrapperImpl::model_materix() const {
    if (model_matrix_should_update()) {
        update_model_matrix();
        _D("Render SingleObject: " << this << " from mobject: " << mobject_
                                   << " with update model: "
                                   << model_matrox_cache_);
    }
    return model_matrox_cache_;
}
bool xcal::render::opengl::utils::SingleMObjectWrapperImpl::
    model_matrix_should_update() const {
    return mobject_->pos().is_changed() || mobject_->rotation().is_changed() ||
           mobject_->scale_x().is_changed() || mobject_->scale_y().is_changed();
}
void xcal::render::opengl::utils::SingleMObjectWrapperImpl::
    update_model_matrix() const {
    model_matrox_cache_ = xcmath::translate(
        xcmath::rotate(
            xcmath::scale(xcmath::mat4<float_t>::eye(),
                          {mobject_->scale_x(), mobject_->scale_y(), 1.0f}),
            mobject_->rotation().value(), {0.0f, 0.0f, 1.0f}),
        {mobject_->pos().x(), mobject_->pos().y(), 0.0f});
    mobject_->pos().reset_changed();
    mobject_->rotation().reset_changed();
    mobject_->scale_x().reset_changed();
    mobject_->scale_y().reset_changed();
}
