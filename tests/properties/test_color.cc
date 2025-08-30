#include <gtest/gtest.h>

#include <mobject/property/color.hpp>

/**
 * @brief 颜色属性测试套件
 *
 * 测试 Color 类的创建、属性访问和格式转换功能。
 */
TEST(TestColor, CreateWithDefaultValues) {
    // 测试默认构造函数
    xcal::mobject::property::Color color;

    EXPECT_EQ(color.r(), 0.0f);
    EXPECT_EQ(color.g(), 0.0f);
    EXPECT_EQ(color.b(), 0.0f);
    EXPECT_EQ(color.a(), 1.0f);
}

TEST(TestColor, CreateWithCustomValues) {
    // 测试自定义参数构造函数
    xcal::mobject::property::Color color(0.5f, 0.6f, 0.7f, 0.8f);

    EXPECT_EQ(color.r(), 0.5f);
    EXPECT_EQ(color.g(), 0.6f);
    EXPECT_EQ(color.b(), 0.7f);
    EXPECT_EQ(color.a(), 0.8f);
}

TEST(TestColor, CreateWithDefaultAlpha) {
    // 测试默认透明度构造函数
    xcal::mobject::property::Color color(0.1f, 0.2f, 0.3f);

    EXPECT_EQ(color.r(), 0.1f);
    EXPECT_EQ(color.g(), 0.2f);
    EXPECT_EQ(color.b(), 0.3f);
    EXPECT_EQ(color.a(), 1.0f);  // 默认透明度应为 1.0
}

TEST(TestColor, ModifyColorComponents) {
    // 测试颜色分量修改功能
    xcal::mobject::property::Color color;

    // 修改各个分量
    color.r() = 0.9f;
    color.g() = 0.8f;
    color.b() = 0.7f;
    color.a() = 0.6f;

    EXPECT_EQ(color.r(), 0.9f);
    EXPECT_EQ(color.g(), 0.8f);
    EXPECT_EQ(color.b(), 0.7f);
    EXPECT_EQ(color.a(), 0.6f);
}

TEST(TestColor, ToHexConversion) {
    // 测试十六进制转换功能
    xcal::mobject::property::Color color(1.0f, 0.0f, 0.0f);  // 红色

    // 红色应该转换为 0xFF0000
    size_t hex = color.to_hex();
    EXPECT_EQ(hex, 0xFF0000u);

    // 绿色测试
    xcal::mobject::property::Color green(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(green.to_hex(), 0x00FF00u);

    // 蓝色测试
    xcal::mobject::property::Color blue(0.0f, 0.0f, 1.0f);
    EXPECT_EQ(blue.to_hex(), 0x0000FFu);

    // 混合颜色测试
    xcal::mobject::property::Color mixed(0.5f, 0.5f, 0.5f);
    EXPECT_EQ(mixed.to_hex(), 0x7F7F7Fu);
}

TEST(TestColor, ToHexStringConversion) {
    // 测试十六进制字符串转换功能
    xcal::mobject::property::Color red(1.0f, 0.0f, 0.0f);
    std::string hexStr = red.to_hex_string();

    // 应该以 # 开头并包含十六进制值
    EXPECT_TRUE(hexStr.starts_with("#"));
    EXPECT_GT(hexStr.size(), 1u);

    // 测试其他颜色
    xcal::mobject::property::Color green(0.0f, 1.0f, 0.0f);
    EXPECT_TRUE(green.to_hex_string().starts_with("#"));
}

TEST(TestColor, ColorComponentRange) {
    // 测试颜色分量范围处理
    xcal::mobject::property::Color color;

    // 测试超出范围的值（应该被接受）
    color.r() = 2.0f;   // 超出 1.0
    color.g() = -1.0f;  // 负值

    EXPECT_EQ(color.r(), 2.0f);
    EXPECT_EQ(color.g(), -1.0f);

    // 测试边界值
    color.r() = 0.0f;
    color.g() = 1.0f;
    color.b() = 0.5f;

    EXPECT_EQ(color.r(), 0.0f);
    EXPECT_EQ(color.g(), 1.0f);
    EXPECT_EQ(color.b(), 0.5f);
}

TEST(TestColor, AlphaComponentBehavior) {
    // 测试透明度分量行为
    xcal::mobject::property::Color transparent(0.5f, 0.5f, 0.5f, 0.0f);
    EXPECT_EQ(transparent.a(), 0.0f);  // 完全透明

    xcal::mobject::property::Color opaque(0.5f, 0.5f, 0.5f, 1.0f);
    EXPECT_EQ(opaque.a(), 1.0f);  // 完全不透明

    xcal::mobject::property::Color semi(0.5f, 0.5f, 0.5f, 0.5f);
    EXPECT_EQ(semi.a(), 0.5f);  // 半透明
}
