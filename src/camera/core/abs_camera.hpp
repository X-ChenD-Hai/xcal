#pragma once
#include <public.h>

#include <camera/core/frame.hpp>
#include <xcmath/xcmath.hpp>
namespace xcal::camera {
class AbsCamera {
   public:
    AbsCamera() {};
    virtual ~AbsCamera() = default;
    virtual xcmath::mat2x2f projection_matrix() const = 0;
};
}  // namespace xcal::camera