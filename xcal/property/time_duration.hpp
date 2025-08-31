#pragma once
#include <string>
#include <xcal/property/core/property.hpp>

namespace xcal::property {

/**
 * @brief 时间段属性类
 *
 * 表示时间间隔或持续时间，使用微秒精度存储。
 * 支持从浮点数秒构造和各种时间单位转换。
 */
class TimeDuration : public MProperty {
    XCAL_PROPERTY_TYPE(TimeDuration)
   private:
    Proxy<size_t> microseconds_{this, 0};  ///< 微秒值

   public:
    /**
     * @brief 默认构造函数
     * @note 创建零时间段
     */
    TimeDuration() : MProperty() {}

    /**
     * @brief 从微秒值构造函数
     * @param microseconds 微秒值
     */
    explicit TimeDuration(size_t microseconds) : MProperty() {
        microseconds_ = microseconds;
    }

    /**
     * @brief 从浮点数秒构造函数
     * @param seconds 秒数（浮点数）
     */
    explicit TimeDuration(float_t seconds) : MProperty() {
        set_seconds(seconds);
    }

    /**
     * @brief 从微秒创建时间段
     * @param us 微秒值
     * @return TimeDuration 对应的时间段对象
     */
    static TimeDuration from_microseconds(size_t us) {
        return TimeDuration(us);
    }

    /**
     * @brief 从毫秒创建时间段
     * @param ms 毫秒值
     * @return TimeDuration 对应的时间段对象
     */
    static TimeDuration from_milliseconds(size_t ms) {
        return TimeDuration(ms * 1000);
    }

    /**
     * @brief 从秒创建时间段
     * @param seconds 秒数（浮点数）
     * @return TimeDuration 对应的时间段对象
     */
    static TimeDuration from_seconds(float_t seconds) {
        return TimeDuration(seconds);
    }

    /**
     * @brief 从分钟创建时间段
     * @param minutes 分钟数（浮点数）
     * @return TimeDuration 对应的时间段对象
     */
    static TimeDuration from_minutes(float_t minutes) {
        return TimeDuration(minutes * 60.0f);
    }

    /**
     * @brief 从小时创建时间段
     * @param hours 小时数（浮点数）
     * @return TimeDuration 对应的时间段对象
     */
    static TimeDuration from_hours(float_t hours) {
        return TimeDuration(hours * 3600.0f);
    }

    /**
     * @brief 获取微秒值
     * @return size_t 微秒值
     */
    size_t microseconds() const { return microseconds_; }

    /**
     * @brief 获取毫秒值
     * @return size_t 毫秒值
     */
    size_t milliseconds() const { return microseconds_ / 1000; }

    /**
     * @brief 获取秒数
     * @return float_t 秒数（浮点数）
     */
    float_t seconds() const {
        return static_cast<float_t>(microseconds_) / 1000000.0f;
    }

    /**
     * @brief 获取分钟数
     * @return float_t 分钟数（浮点数）
     */
    float_t minutes() const {
        return static_cast<float_t>(microseconds_) / 60000000.0f;
    }

    /**
     * @brief 获取小时数
     * @return float_t 小时数（浮点数）
     */
    float_t hours() const {
        return static_cast<float_t>(microseconds_) / 3600000000.0f;
    }

    /**
     * @brief 设置微秒值
     * @param us 微秒值
     */
    void set_microseconds(size_t us) { microseconds_ = us; }

    /**
     * @brief 设置毫秒值
     * @param ms 毫秒值
     */
    void set_milliseconds(size_t ms) { microseconds_ = ms * 1000; }

    /**
     * @brief 设置秒数
     * @param seconds 秒数（浮点数）
     */
    void set_seconds(float_t seconds) {
        microseconds_ = static_cast<size_t>(seconds * 1000000.0f);
    }

    /**
     * @brief 设置分钟数
     * @param minutes 分钟数（浮点数）
     */
    void set_minutes(float_t minutes) { set_seconds(minutes * 60.0f); }

    /**
     * @brief 设置小时数
     * @param hours 小时数（浮点数）
     */
    void set_hours(float_t hours) { set_seconds(hours * 3600.0f); }

    /**
     * @brief 时间段加法运算
     * @param other 另一个时间段
     * @return TimeDuration 相加后的时间段
     */
    TimeDuration operator+(const TimeDuration& other) const {
        return TimeDuration(microseconds_ + other.microseconds_);
    }

    /**
     * @brief 时间段减法运算
     * @param other 另一个时间段
     * @return TimeDuration 相减后的时间段
     */
    TimeDuration operator-(const TimeDuration& other) const {
        return TimeDuration(microseconds_ - other.microseconds_);
    }

    /**
     * @brief 时间段乘法运算
     * @param multiplier 乘数
     * @return TimeDuration 相乘后的时间段
     */
    TimeDuration operator*(size_t multiplier) const {
        return TimeDuration(microseconds_ * multiplier);
    }

    /**
     * @brief 时间段除法运算
     * @param divisor 除数
     * @return TimeDuration 相除后的时间段
     */
    TimeDuration operator/(size_t divisor) const {
        return TimeDuration(microseconds_ / divisor);
    }

    /**
     * @brief 时间段相等比较
     * @param other 另一个时间段
     * @return bool 是否相等
     */
    bool operator==(const TimeDuration& other) const {
        return microseconds_ == other.microseconds_;
    }

    /**
     * @brief 时间段不等比较
     * @param other 另一个时间段
     * @return bool 是否不等
     */
    bool operator!=(const TimeDuration& other) const {
        return !(*this == other);
    }

    /**
     * @brief 时间段小于比较
     * @param other 另一个时间段
     * @return bool 是否小于
     */
    bool operator<(const TimeDuration& other) const {
        return microseconds_ < other.microseconds_;
    }

    /**
     * @brief 时间段大于比较
     * @param other 另一个时间段
     * @return bool 是否大于
     */
    bool operator>(const TimeDuration& other) const {
        return microseconds_ > other.microseconds_;
    }

    /**
     * @brief 时间段小于等于比较
     * @param other 另一个时间段
     * @return bool 是否小于等于
     */
    bool operator<=(const TimeDuration& other) const {
        return microseconds_ <= other.microseconds_;
    }

    /**
     * @brief 时间段大于等于比较
     * @param other 另一个时间段
     * @return bool 是否大于等于
     */
    bool operator>=(const TimeDuration& other) const {
        return microseconds_ >= other.microseconds_;
    }

    /**
     * @brief 转换为字符串表示
     * @return std::string 时间段的字符串表示
     */
    std::string to_string() const {
        if (microseconds_ < 1000) {
            return std::to_string(microseconds_) + "us";
        } else if (microseconds_ < 1000000) {
            return std::to_string(milliseconds()) + "ms";
        } else {
            return std::to_string(seconds()) + "s";
        }
    }
};

}  // namespace xcal::property
