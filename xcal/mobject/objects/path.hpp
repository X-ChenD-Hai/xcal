#pragma once
#include <xcal/mobject/core/mobject.hpp>
#include <xcal/property/position_list.hpp>

namespace xcal::mobject {

class Path : public MObject {
    XCAL_MOBJECT_TYPE(Path)
   private:
    property::PositionList points_;

   public:
    Path(property::PositionList points)
        : MObject(), points_(std::move(points)) {
        register_properties(points_);
    }
    const property::PositionList& points() const { return points_; }
    void set_points(const property::PositionList& points) { points_ = points; }
    virtual ~Path() override = default;
};

}  // namespace xcal::mobject
