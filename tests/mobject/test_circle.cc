#include <gtest/gtest.h>

#include <mobject/objects/circle.hpp>

/**
 * @brief 圆形对象测试套件
 *
 * 测试 Circle 类的创建、属性访问和修改功能。
 */
TEST(TestCircle, CreateWithDefaultValues) {
    // 测试默认构造函数
    auto circle = std::make_unique<xcal::mobject::Circle>();
    EXPECT_EQ(circle->radius(), 1.0f);
    EXPECT_EQ(circle->pos().x(), 0.0f);
    EXPECT_EQ(circle->pos().y(), 0.0f);
    EXPECT_TRUE(circle->visible());
}

TEST(TestCircle, CreateWithCustomValues) {
    // 测试自定义参数构造函数
    auto circle = std::make_unique<xcal::mobject::Circle>(
        xcal::property::Position{2.0f, 3.0f}, 5.0f);

    EXPECT_EQ(circle->radius(), 5.0f);
    EXPECT_EQ(circle->pos().x(), 2.0f);
    EXPECT_EQ(circle->pos().y(), 3.0f);
}

TEST(TestCircle, SetRadius) {
    // 测试半径设置功能
    auto circle = std::make_unique<xcal::mobject::Circle>();

    // 初始半径应为默认值
    EXPECT_EQ(circle->radius(), 1.0f);

    // 设置新半径
    circle->set_radius(10.0f);
    EXPECT_EQ(circle->radius(), 10.0f);

    // 设置零半径
    circle->set_radius(0.0f);
    EXPECT_EQ(circle->radius(), 0.0f);

    // 设置负半径（应允许，但可能在实际渲染中处理）
    circle->set_radius(-5.0f);
    EXPECT_EQ(circle->radius(), -5.0f);
}

TEST(TestCircle, PositionInheritance) {
    // 测试从 MObject 继承的位置功能
    auto circle = std::make_unique<xcal::mobject::Circle>(
        xcal::property::Position{7.0f, 8.0f}, 2.0f);

    // 验证位置继承
    EXPECT_EQ(circle->pos().x(), 7.0f);
    EXPECT_EQ(circle->pos().y(), 8.0f);

    // 验证位置可修改
    circle->pos().x() = 9.0f;
    circle->pos().y() = 10.0f;
    EXPECT_EQ(circle->pos().x(), 9.0f);
    EXPECT_EQ(circle->pos().y(), 10.0f);
}

TEST(TestCircle, VisibilityInheritance) {
    // 测试从 AbsMObject 继承的可见性功能
    auto circle = std::make_unique<xcal::mobject::Circle>();

    // 初始应为可见
    EXPECT_TRUE(circle->visible());

    // 设置为不可见
    circle->visible() = false;
    EXPECT_FALSE(circle->visible());

    // 重新设置为可见
    circle->visible() = true;
    EXPECT_TRUE(circle->visible());
}

TEST(TestCircle, PropertiesRegistration) {
    // 测试属性注册功能
    auto circle = std::make_unique<xcal::mobject::Circle>();

    // 验证属性列表包含半径属性
    auto& properties = circle->properties();
    EXPECT_FALSE(properties.empty());

    // 应该至少有一个属性（半径）
    EXPECT_GE(properties.size(), 1);
}
