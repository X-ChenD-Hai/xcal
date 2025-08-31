#pragma once
#include <xcal/mobject/core/mobject.hpp>
#include <xcal/property/position_list.hpp>

namespace xcal::mobject {

class Polygone : public MObject {
    XCAL_MOBJECT_TYPE(Polygone)
   private:
    property::PositionList points_;

   public:
    Polygone() : MObject(), points_({}) { register_properties(points_); }
    template <typename... Args>
        requires std::constructible_from<property::PositionList, Args...>
    Polygone(Args&&... args)
        : MObject(),
          points_(std::make_unique<property::PositionList>(
              std::forward<Args>(args)...)) {
        register_properties(points_);
        points_.closed() = true;
    }
    const std::vector<property::Position>& points() const {
        return points_.positions();
    }
    void set_points(const property::PositionList& points) { points_ = points; }
    virtual ~Polygone() override = default;
};

}  // namespace xcal::mobject
