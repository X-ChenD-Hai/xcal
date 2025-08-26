#pragma once
#include <mobject/core/mobject.hpp>

namespace xcal::mobject {

class Line : public MObject {
    XCAL_MOBJECT_TYPE(Line)
   private:
    property::Position start_;
    property::Position end_;

   public:
    Line(property::Position start, property::Position end)
        : MObject(start), start_(start), end_(end) {
        register_properties(start_, end_);
    }
    const property::Position& start() const { return start_; }
    property::Position& start() { return start_; }
    const property::Position& end() const { return end_; }
    property::Position& end() { return end_; }
    virtual ~Line() override = default;
};

}  // namespace xcal::mobject
