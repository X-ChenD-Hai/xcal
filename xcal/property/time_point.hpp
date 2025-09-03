#pragma once
#include <chrono>
#include <string>
#include <xcal/property/core/property.hpp>
#include <xcal/property/time_duration.hpp>

namespace xcal::property {

/**
 * @brief 时间点属性类
 *
 * 表示特定的时间点，使用从纪元开始的微秒数存储。
 * 支持从浮点数秒构造和时间运算。
 */
class XCAL_API TimePoint : public MProperty {
    XCAL_PROPERTY_TYPE(TimePoint)
   private:
    Proxy<size_t> microseconds_since_epoch_{this, 0};  ///< 从纪元开始的微秒数

   public:
    /**
     * @brief 默认构造函数
     * @note 创建纪元时间点 (1970-01-01 00:00:00)
     */
    TimePoint() : MProperty() {}

    /**
     * @brief 从浮点数秒构造函数
     * @param seconds_since_epoch 从纪元开始的秒数（浮点数）
     */
    explicit TimePoint(float_t seconds_since_epoch) : MProperty() {
        set_seconds_since_epoch(seconds_since_epoch);
    }

    /**
     * @brief 获取当前时间点
     * @return TimePoint 当前时间点
     */
    static TimePoint now() {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto microseconds =
            std::chrono::duration_cast<std::chrono::microseconds>(duration)
                .count();
        TimePoint timePoint;
        timePoint.set_microseconds_since_epoch(
            static_cast<size_t>(microseconds));
        return timePoint;
    }

    /**
     * @brief 获取从纪元开始的微秒数
     * @return size_t 微秒数
     */
    size_t microseconds_since_epoch() const {
        return microseconds_since_epoch_;
    }

    /**
     * @brief 获取从纪元开始的秒数
     * @return float_t 秒数（浮点数）
     */
    float_t seconds_since_epoch() const {
        return static_cast<float_t>(microseconds_since_epoch_) / 1000000.0f;
    }

    /**
     * @brief 设置从纪元开始的微秒数
     * @param us 微秒数
     */
    void set_microseconds_since_epoch(size_t us) {
        microseconds_since_epoch_ = us;
    }

    /**
     * @brief 设置从纪元开始的秒数
     * @param seconds 秒数（浮点数）
     */
    void set_seconds_since_epoch(float_t seconds) {
        microseconds_since_epoch_ = static_cast<size_t>(seconds * 1000000.0f);
    }

    /**
     * @brief 时间点加法运算（添加时间段）
     * @param duration 要添加的时间段
     * @return TimePoint 相加后的时间点
     */
    TimePoint operator+(const TimeDuration& duration) const {
        TimePoint result;
        result.set_microseconds_since_epoch(microseconds_since_epoch_ +
                                            duration.microseconds());
        return result;
    }

    /**
     * @brief 时间点减法运算（减去时间段）
     * @param duration 要减去的时间段
     * @return TimePoint 相减后的时间点
     */
    TimePoint operator-(const TimeDuration& duration) const {
        TimePoint result;
        result.set_microseconds_since_epoch(microseconds_since_epoch_ -
                                            duration.microseconds());
        return result;
    }

    /**
     * @brief 时间点减法运算（计算时间差）
     * @param other 另一个时间点
     * @return TimeDuration 两个时间点之间的时间段
     */
    TimeDuration operator-(const TimePoint& other) const {
        return TimeDuration(microseconds_since_epoch_ -
                            other.microseconds_since_epoch_);
    }

    /**
     * @brief 时间点相等比较
     * @param other 另一个时间点
     * @return bool 是否相等
     */
    bool operator==(const TimePoint& other) const {
        return microseconds_since_epoch_ == other.microseconds_since_epoch_;
    }

    /**
     * @brief 时间点不等比较
     * @param other 另一个时间点
     * @return bool 是否不等
     */
    bool operator!=(const TimePoint& other) const { return !(*this == other); }

    /**
     * @brief 时间点小于比较
     * @param other 另一个时间点
     * @return bool 是否小于
     */
    bool operator<(const TimePoint& other) const {
        return microseconds_since_epoch_ < other.microseconds_since_epoch_;
    }

    /**
     * @brief 时间点大于比较
     * @param other 另一个时间点
     * @return bool 是否大于
     */
    bool operator>(const TimePoint& other) const {
        return microseconds_since_epoch_ > other.microseconds_since_epoch_;
    }

    /**
     * @brief 时间点小于等于比较
     * @param other 另一个时间点
     * @return bool 是否小于等于
     */
    bool operator<=(const TimePoint& other) const {
        return microseconds_since_epoch_ <= other.microseconds_since_epoch_;
    }

    /**
     * @brief 时间点大于等于比较
     * @param other 另一个时间点
     * @return bool 是否大于等于
     */
    bool operator>=(const TimePoint& other) const {
        return microseconds_since_epoch_ >= other.microseconds_since_epoch_;
    }

    /**
     * @brief 转换为字符串表示
     * @return std::string 时间点的字符串表示
     */
    std::string to_string() const {
        // 简单的字符串表示，可以扩展为更复杂的格式
        return std::to_string(seconds_since_epoch()) + "s since epoch";
    }

    /**
     * @brief 格式化时间输出
     * @param format_pattern 格式模式（TODO: 实现具体格式化逻辑）
     * @return std::string 格式化后的时间字符串
     */
    std::string format(const std::string& format_pattern) const {
        // 占位实现，可以根据需要扩展具体的格式化逻辑
        return to_string();
    }
};

}  // namespace xcal::property
