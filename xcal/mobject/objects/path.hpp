#pragma once
#include <xcal/mobject/core/mobject.hpp>
#include <xcal/property/position_list.hpp>

#include "xcal/public.h"

namespace xcal::mobject {

class XCAL_API Path : public MObject {
    XCAL_MOBJECT_TYPE(Path)
   public:
    using vec = xcmath::vec2<float_t>;
    using data_t = std::vector<vec>;

   private:
    property::PositionList points_;

   public:
    Path() : Path(property::PositionList::data_t(), false) {}
    Path(const property::PositionList::data_t& list) : Path(list, false) {}
    Path(const property::PositionList::data_t& list, bool_t closed)
        : points_(list, closed) {}

    const property::PositionList& points() const { return points_; }
    void set_points(const property::PositionList::data_t& points) {
        points_ = points;
    }
    virtual ~Path() override = default;
    Path(const Path&) = delete;
    Path(Path&&) = delete;
    Path& operator=(const Path&) = delete;
    Path& operator=(Path&&) = delete;
};
}  // namespace xcal::mobject
