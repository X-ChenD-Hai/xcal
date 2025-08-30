#include <gtest/gtest.h>

#include <mobject/property/time_duration.hpp>
#include <mobject/property/time_point.hpp>

/**
 * @brief 时间点属性测试套件
 *
 * 测试 TimePoint 类的创建、属性访问和运算功能。
 */
TEST(TestTimePoint, CreateWithDefaultValues) {
    // 测试默认构造函数
    xcal::mobject::property::TimePoint timePoint;

    EXPECT_EQ(timePoint.microseconds_since_epoch(), 0u);
    EXPECT_FLOAT_EQ(timePoint.seconds_since_epoch(), 0.0f);
}

TEST(TestTimePoint, CreateFromFloatSeconds) {
    // 测试从浮点数秒创建
    xcal::mobject::property::TimePoint timePoint(2.75f);  // 2.75秒从纪元开始

    EXPECT_EQ(timePoint.microseconds_since_epoch(), 2750000u);
    EXPECT_FLOAT_EQ(timePoint.seconds_since_epoch(), 2.75f);
}

TEST(TestTimePoint, SetterMethods) {
    // 测试设置方法
    xcal::mobject::property::TimePoint timePoint;

    timePoint.set_microseconds_since_epoch(1000000u);
    EXPECT_EQ(timePoint.microseconds_since_epoch(), 1000000u);

    timePoint.set_seconds_since_epoch(1.25f);
    EXPECT_FLOAT_EQ(timePoint.seconds_since_epoch(), 1.25f);
}

TEST(TestTimePoint, NowMethod) {
    // 测试获取当前时间点
    xcal::mobject::property::TimePoint now =
        xcal::mobject::property::TimePoint::now();

    // 当前时间应该大于纪元时间
    EXPECT_GT(now.microseconds_since_epoch(), 0u);
    EXPECT_GT(now.seconds_since_epoch(), 0.0f);
}

TEST(TestTimePoint, TimePointArithmetic) {
    // 测试时间点运算
    xcal::mobject::property::TimePoint tp1;
    tp1.set_microseconds_since_epoch(1000000u);  // 1秒从纪元开始

    xcal::mobject::property::TimeDuration duration =
        xcal::mobject::property::TimeDuration::from_microseconds(
            500000u);  // 0.5秒

    // 时间点加法
    auto later = tp1 + duration;
    EXPECT_EQ(later.microseconds_since_epoch(), 1500000u);

    // 时间点减法
    auto earlier = tp1 - duration;
    EXPECT_EQ(earlier.microseconds_since_epoch(), 500000u);
}

TEST(TestTimePoint, TimePointSubtraction) {
    // 测试时间点相减得到时间段
    xcal::mobject::property::TimePoint tp1;
    tp1.set_microseconds_since_epoch(2000000u);  // 2秒从纪元开始

    xcal::mobject::property::TimePoint tp2;
    tp2.set_microseconds_since_epoch(500000u);  // 0.5秒从纪元开始

    // 时间点相减得到时间段
    auto duration = tp1 - tp2;
    EXPECT_EQ(duration.microseconds(), 1500000u);
    EXPECT_FLOAT_EQ(duration.seconds(), 1.5f);
}

TEST(TestTimePoint, ComparisonOperations) {
    // 测试比较运算
    xcal::mobject::property::TimePoint tp1;
    tp1.set_microseconds_since_epoch(1000000u);  // 1秒从纪元开始

    xcal::mobject::property::TimePoint tp2;
    tp2.set_microseconds_since_epoch(2000000u);  // 2秒从纪元开始

    xcal::mobject::property::TimePoint tp3;
    tp3.set_microseconds_since_epoch(1000000u);  // 1秒从纪元开始

    EXPECT_TRUE(tp1 == tp3);
    EXPECT_TRUE(tp1 != tp2);
    EXPECT_TRUE(tp1 < tp2);
    EXPECT_TRUE(tp2 > tp1);
    EXPECT_TRUE(tp1 <= tp3);
    EXPECT_TRUE(tp1 >= tp3);
    EXPECT_TRUE(tp1 <= tp2);
    EXPECT_TRUE(tp2 >= tp1);
}

TEST(TestTimePoint, ToStringConversion) {
    // 测试字符串转换
    xcal::mobject::property::TimePoint timePoint;
    timePoint.set_microseconds_since_epoch(1234567u);  // 1.234567秒从纪元开始

    std::string str = timePoint.to_string();
    EXPECT_TRUE(str.find("1.234567") != std::string::npos);
    EXPECT_TRUE(str.find("s since epoch") != std::string::npos);
}

TEST(TestTimePoint, FormatMethod) {
    // 测试格式化方法
    xcal::mobject::property::TimePoint timePoint;
    timePoint.set_microseconds_since_epoch(1000000u);  // 1秒从纪元开始

    // 格式化方法应该返回有效的字符串
    std::string formatted = timePoint.format("dummy pattern");
    EXPECT_FALSE(formatted.empty());
}

TEST(TestTimePoint, PrecisionConversion) {
    // 测试精度转换
    xcal::mobject::property::TimePoint timePoint;
    timePoint.set_microseconds_since_epoch(1234567u);  // 1.234567秒从纪元开始

    // 验证浮点数转换的精度
    EXPECT_NEAR(timePoint.seconds_since_epoch(), 1.234567f, 0.000001f);
}
