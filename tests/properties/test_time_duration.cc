#include <gtest/gtest.h>

#include <xcal/property/time_duration.hpp>

/**
 * @brief 时间段属性测试套件
 *
 * 测试 TimeDuration 类的创建、属性访问和运算功能。
 */
TEST(TestTimeDuration, CreateWithDefaultValues) {
    // 测试默认构造函数
    xcal::property::TimeDuration duration;

    EXPECT_EQ(duration.microseconds(), 0u);
    EXPECT_EQ(duration.milliseconds(), 0u);
    EXPECT_FLOAT_EQ(duration.seconds(), 0.0f);
    EXPECT_FLOAT_EQ(duration.minutes(), 0.0f);
    EXPECT_FLOAT_EQ(duration.hours(), 0.0f);
}

TEST(TestTimeDuration, CreateFromMicroseconds) {
    // 测试从微秒创建
    xcal::property::TimeDuration duration =
        xcal::property::TimeDuration::from_microseconds(1500000u);  // 1.5秒

    EXPECT_EQ(duration.microseconds(), 1500000u);
    EXPECT_EQ(duration.milliseconds(), 1500u);
    EXPECT_FLOAT_EQ(duration.seconds(), 1.5f);
}

TEST(TestTimeDuration, CreateFromFloatSeconds) {
    // 测试从浮点数秒创建
    xcal::property::TimeDuration duration =
        xcal::property::TimeDuration::from_seconds(2.75f);  // 2.75秒

    EXPECT_EQ(duration.microseconds(), 2750000u);
    EXPECT_FLOAT_EQ(duration.seconds(), 2.75f);
}

TEST(TestTimeDuration, StaticFactoryMethods) {
    // 测试静态工厂方法
    auto fromUs = xcal::property::TimeDuration::from_microseconds(500000u);
    EXPECT_EQ(fromUs.microseconds(), 500000u);

    auto fromMs = xcal::property::TimeDuration::from_milliseconds(2500u);
    EXPECT_EQ(fromMs.milliseconds(), 2500u);
    EXPECT_EQ(fromMs.microseconds(), 2500000u);

    auto fromSec = xcal::property::TimeDuration::from_seconds(3.14f);
    EXPECT_FLOAT_EQ(fromSec.seconds(), 3.14f);

    auto fromMin = xcal::property::TimeDuration::from_minutes(1.5f);
    EXPECT_FLOAT_EQ(fromMin.minutes(), 1.5f);
    EXPECT_FLOAT_EQ(fromMin.seconds(), 90.0f);

    auto fromHour = xcal::property::TimeDuration::from_hours(0.5f);
    EXPECT_FLOAT_EQ(fromHour.hours(), 0.5f);
    EXPECT_FLOAT_EQ(fromHour.minutes(), 30.0f);
}

TEST(TestTimeDuration, SetterMethods) {
    // 测试设置方法
    xcal::property::TimeDuration duration;

    duration.set_microseconds(1000000u);
    EXPECT_EQ(duration.microseconds(), 1000000u);

    duration.set_milliseconds(2000u);
    EXPECT_EQ(duration.milliseconds(), 2000u);

    duration.set_seconds(1.25f);
    EXPECT_FLOAT_EQ(duration.seconds(), 1.25f);

    duration.set_minutes(2.0f);
    EXPECT_FLOAT_EQ(duration.minutes(), 2.0f);

    duration.set_hours(0.25f);
    EXPECT_FLOAT_EQ(duration.hours(), 0.25f);
}

TEST(TestTimeDuration, ArithmeticOperations) {
    // 测试算术运算
    xcal::property::TimeDuration d1 =
        xcal::property::TimeDuration::from_microseconds(1000000u);  // 1秒
    xcal::property::TimeDuration d2 =
        xcal::property::TimeDuration::from_microseconds(500000u);  // 0.5秒

    // 加法
    auto sum = d1 + d2;
    EXPECT_EQ(sum.microseconds(), 1500000u);

    // 减法
    auto diff = d1 - d2;
    EXPECT_EQ(diff.microseconds(), 500000u);

    // 乘法
    auto multiplied = d1 * 3;
    EXPECT_EQ(multiplied.microseconds(), 3000000u);

    // 除法
    auto divided = d1 / 2;
    EXPECT_EQ(divided.microseconds(), 500000u);
}

TEST(TestTimeDuration, ComparisonOperations) {
    // 测试比较运算
    xcal::property::TimeDuration d1 =
        xcal::property::TimeDuration::from_microseconds(1000000u);  // 1秒
    xcal::property::TimeDuration d2 =
        xcal::property::TimeDuration::from_microseconds(2000000u);  // 2秒
    xcal::property::TimeDuration d3 =
        xcal::property::TimeDuration::from_microseconds(1000000u);  // 1秒

    EXPECT_TRUE(d1 == d3);
    EXPECT_TRUE(d1 != d2);
    EXPECT_TRUE(d1 < d2);
    EXPECT_TRUE(d2 > d1);
    EXPECT_TRUE(d1 <= d3);
    EXPECT_TRUE(d1 >= d3);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d2 >= d1);
}

TEST(TestTimeDuration, ToStringConversion) {
    // 测试字符串转换
    xcal::property::TimeDuration micro =
        xcal::property::TimeDuration::from_microseconds(500u);  // 500微秒
    xcal::property::TimeDuration milli =
        xcal::property::TimeDuration::from_microseconds(1500u);  // 1.5毫秒
    xcal::property::TimeDuration sec =
        xcal::property::TimeDuration::from_microseconds(2500000u);  // 2.5秒

    EXPECT_TRUE(micro.to_string().find("us") != std::string::npos);
    EXPECT_TRUE(milli.to_string().find("ms") != std::string::npos);
    EXPECT_TRUE(sec.to_string().find("s") != std::string::npos);
}

TEST(TestTimeDuration, PrecisionConversion) {
    // 测试精度转换
    xcal::property::TimeDuration duration =
        xcal::property::TimeDuration::from_microseconds(
            1234567u);  // 1.234567秒

    // 验证浮点数转换的精度
    EXPECT_NEAR(duration.seconds(), 1.234567f, 0.000001f);
    EXPECT_NEAR(duration.minutes(), 1.234567f / 60.0f, 0.000001f);
    EXPECT_NEAR(duration.hours(), 1.234567f / 3600.0f, 0.000001f);
}
