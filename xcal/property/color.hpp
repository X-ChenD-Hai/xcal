#pragma once
#include <array>
#include <string>
#include <xcal/property/core/property.hpp>


namespace xcal::property {

/**
 * @brief 颜色属性类
 *
 * 表示 RGBA 颜色属性，继承自 MProperty 基类。
 * 支持颜色值的获取、设置和格式转换。
 */
class Color : public MProperty {
    XCAL_PROPERTY_TYPE(Color)
   private:
    Proxy<std::array<float_t, 4>> data_ = {{0.0, 0.0, 0.0, 1.0},
                                           this};  ///< RGBA 颜色数据

   public:
    /**
     * @brief 默认构造函数
     * @note 创建黑色不透明颜色 (0.0, 0.0, 0.0, 1.0)
     */
    Color() : MProperty() {}

    /**
     * @brief 构造函数
     * @param r 红色分量 (0.0-1.0)
     * @param g 绿色分量 (0.0-1.0)
     * @param b 蓝色分量 (0.0-1.0)
     * @param a 透明度分量 (0.0-1.0)，默认为 1.0（不透明）
     */
    Color(float_t r, float_t g, float_t b, float_t a = 1.0) {
        data_ = {{r, g, b, a}};
    }

    /**
     * @brief 获取红色分量（只读）
     * @return const float_t& 红色分量引用
     */
    const float_t &r() const { return data_[0]; }

    /**
     * @brief 获取绿色分量（只读）
     * @return const float_t& 绿色分量引用
     */
    const float_t &g() const { return data_[1]; }

    /**
     * @brief 获取蓝色分量（只读）
     * @return const float_t& 蓝色分量引用
     */
    const float_t &b() const { return data_[2]; }

    /**
     * @brief 获取透明度分量（只读）
     * @return const float_t& 透明度分量引用
     */
    const float_t &a() const { return data_[3]; }

    /**
     * @brief 获取红色分量（可修改）
     * @return float_t& 红色分量引用
     */
    float_t &r() { return data_[0]; }

    /**
     * @brief 获取绿色分量（可修改）
     * @return float_t& 绿色分量引用
     */
    float_t &g() { return data_[1]; }

    /**
     * @brief 获取蓝色分量（可修改）
     * @return float_t& 蓝色分量引用
     */
    float_t &b() { return data_[2]; }

    /**
     * @brief 获取透明度分量（可修改）
     * @return float_t& 透明度分量引用
     */
    float_t &a() { return data_[3]; }

    /**
     * @brief 将颜色转换为十六进制数值
     * @return size_t 十六进制颜色值（格式：0xRRGGBB）
     * @note 透明度分量不参与计算
     */
    size_t to_hex() {
        return ((size_t(data_[0] * 255) << 16) | (size_t(data_[1] * 255) << 8) |
                size_t(data_[2] * 255));
    }

    /**
     * @brief 将颜色转换为十六进制字符串
     * @return std::string 十六进制颜色字符串（格式："#RRGGBB"）
     */
    std::string to_hex_string() {
        return "#" + std::string(std::to_string(to_hex()));
    }

    /**
     * @brief 从十六进制数值创建颜色
     * @param hex 十六进制颜色值（格式：0xRRGGBB）
     * @return Color 对应的颜色对象
     * @note 透明度设置为 1.0（不透明）
     */
    static Color from_hex(uint32_t hex);

    /**
     * @brief 从颜色名称创建颜色
     * @param name 颜色名称（如 "red", "blue" 等）
     * @return Color 对应的颜色对象
     * @note 支持常见颜色名称，不区分大小写
     */
    static Color from_name(const std::string &name);

    /**
     * @brief 从十六进制字符串创建颜色
     * @param hex 十六进制颜色字符串（格式："#RRGGBB" 或 "RRGGBB"）
     * @return Color 对应的颜色对象
     * @note 透明度设置为 1.0（不透明）
     */
    static Color from_hex(const std::string &hex);
};

}  // namespace xcal::property
