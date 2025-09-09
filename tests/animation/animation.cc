#include <gtest/gtest.h>

#include <memory>
#include <xcal/animation/Interpolation.hpp>
#include <xcal/animation/core/timeline.hpp>
#include <xcal/animation/core/timelinedriver.hpp>
#include <xcal/property/scalar.hpp>

TEST(TestAnimation, Test1) {
    using namespace xcal::animation;
    using namespace xcal::property;

    auto timeline = std::make_unique<Timeline>();
    auto property = std::make_unique<Scalar>(0);
    auto animation =
        std::make_unique<ScalerInterpolation>(property.get(), 0.0f, 100.0f);
    timeline->add(animation.get(), 0, 1);
    auto driver = std::make_unique<TimelineDriver>(timeline.get());
    driver->set_frame_rate(60)->ready_to_play();
    while (!driver->finished()) {
        std::cout << "------------- start new frame -----------------"
                  << std::endl;
        driver->next();
        if (property->is_changed()) {
            std::cout << "property value: " << property->value() << std::endl;
            property->reset_changed();
        }
        std::cout << "------------- end new frame -----------------"
                  << std::endl;
    }
}