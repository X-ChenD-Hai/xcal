#include <gtest/gtest.h>

#include <xcal/mobject/core/mobject.hpp>

using namespace xcal::mobject;

class TestMObject : public MObject {
    XCAL_MOBJECT_TYPE(Unknown);

   public:
    using MObject::MObject;
};

// 允许使用 EXPECT_NEAR 比较 float
static constexpr float EPS = 1e-4f;

TEST(TestMObject, Constructor) {
    TestMObject obj;
    EXPECT_EQ(obj.pos().x(), 0.0f);
    EXPECT_EQ(obj.pos().y(), 0.0f);
}

TEST(TestMObject, LocalGlobal_NoTransform) {
    TestMObject obj;
    obj.set_pos({3.0f, 4.0f});

    auto g = obj.local_to_global({1.0f, 2.0f, 0.0f, 1.0f});
    EXPECT_NEAR(g.x(), 4.0f, EPS);
    EXPECT_NEAR(g.y(), 6.0f, EPS);

    auto l = obj.global_to_local({4.0f, 6.0f, 0.0f, 1.0f});
    EXPECT_NEAR(l.x(), 1.0f, EPS);
    EXPECT_NEAR(l.y(), 2.0f, EPS);
}

TEST(TestMObject, LocalGlobal_RotationOnly) {
    TestMObject obj;
    obj.set_pos({2.0f, 1.0f});
    obj.set_rotation(90.0f);  // 90°

    auto g = obj.local_to_global({1.0f, 0.0f, 0.0f, 1.0f});
    EXPECT_NEAR(g.x(), 2.0f, EPS);
    EXPECT_NEAR(g.y(), 2.0f, EPS);

    auto l = obj.global_to_local({2.0f, 2.0f, 0.0f, 1.0f});
    EXPECT_NEAR(l.x(), 1.0f, EPS);
    EXPECT_NEAR(l.y(), 0.0f, EPS);
}

TEST(TestMObject, LocalGlobal_ScaleOnly) {
    TestMObject obj;
    obj.set_pos({0.0f, 0.0f});
    obj.set_scale(2.0f, 3.0f);

    auto g = obj.local_to_global({1.0f, 1.0f, 0.0f, 1.0f});
    EXPECT_NEAR(g.x(), 2.0f, EPS);
    EXPECT_NEAR(g.y(), 3.0f, EPS);

    auto l = obj.global_to_local({2.0f, 3.0f, 0.0f, 1.0f});
    EXPECT_NEAR(l.x(), 1.0f, EPS);
    EXPECT_NEAR(l.y(), 1.0f, EPS);
}

TEST(TestMObject, LocalGlobal_Complex) {
    TestMObject obj;
    obj.set_pos({5.0f, 5.0f});
    obj.set_rotation(45.0f);  // 45°
    obj.set_scale(2.0f, 2.0f);

    // 已知 local = (1,0)
    auto g = obj.local_to_global({1.0f, 0.0f, 0.0f, 1.0f});
    // 旋转45°再*2 => (cos45*2, sin45*2) ≈ (1.4142, 1.4142)
    // 再加平移 => (6.4142, 6.4142)
    EXPECT_NEAR(g.x(), 5.0f + 1.4142135f, EPS);
    EXPECT_NEAR(g.y(), 5.0f + 1.4142135f, EPS);

    // 反向映射
    auto l = obj.global_to_local({g.x(), g.y(), 0.0f, 1.0f});
    EXPECT_NEAR(l.x(), 1.0f, EPS);
    EXPECT_NEAR(l.y(), 0.0f, EPS);
}