#pragma once
#include <xcal/mobject/core/mobject.hpp>
#include <xcal/property/position_list.hpp>

namespace xcal::mobject {

class XCAL_API Path : public MObject {
    XCAL_MOBJECT_TYPE(Path)
   private:
    property::PositionList points_;

   public:
    template <typename... Args>
        requires(std::is_constructible_v<property::PositionList, Args...>)
    Path(Args&&... points) : MObject(), points_(std::forward<Args>(points)...) {
        register_properties(points_);
    }
    const property::PositionList& points() const { return points_; }
    void set_points(const property::PositionList::data_t& points) {
        points_ = points;
    }
    virtual ~Path() override = default;
};

}  // namespace xcal::mobject
