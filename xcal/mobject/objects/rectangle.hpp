#pragma once
#include <xcal/public.h>

#include <xcal/mobject/core/composedmobject.hpp>
#include <xcal/mobject/core/mobject.hpp>

#include "xcal/property/vec.hpp"

namespace xcal::mobject {

class XCAL_API Rectangle
    : public ComposedMObject<Rectangle, BaseTransformableMobject,
                             StrokeableMObject> {
    XCAL_MOBJECT_TYPE(Rectangle)
   private:
    property::Position pos_;
    property::Scalar width_;
    property::Scalar height_;

   public:
    Rectangle(const property::Vec<float, 3>::data_t& pos, float_t width,
              float_t height)
        : width_(width), height_(height) {
        set_pos(pos);
        register_properties(pos_, width_, height_);
    }
    const property::Scalar& width() const { return width_; }
    property::Scalar& width() { return width_; }
    const property::Scalar& height() const { return height_; }
    property::Scalar& height() { return height_; }
    virtual ~Rectangle() override = default;
};

}  // namespace xcal::mobject
