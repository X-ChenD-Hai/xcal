#include <gtest/gtest.h>

#include <scene/scene.hpp>

TEST(property, proxy) {
    // xcal::scene::AbsScene scene;
    // xcal::mobject::Circle obj;
    xcal::mobject::property::Scalar radius{11};
    radius.reset_changed();
    std::cout << radius.is_changed() << std::endl;
    std::cout << (radius = 12) << std::endl;
    std::cout << radius.is_changed() << std::endl;
}