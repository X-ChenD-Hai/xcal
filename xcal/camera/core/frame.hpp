/**
 * @file frame.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief 帧处理类
 * @version 0.1
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <xcal/public.h>

#include <cstddef>

namespace xcal::camera {

/**
 * @brief 颜色格式枚举
 *
 * 定义支持的图像颜色格式
 */
enum class ColorFormat {
    BGR,     ///< BGR 颜色格式
    RGB,     ///< RGB 颜色格式
    RGBA,    ///< RGBA 颜色格式（带透明度）
    Gray,    ///< 灰度格式
    YUV420,  ///< YUV 4:2:0 格式
    YUV422,  ///< YUV 4:2:2 格式
    YUV444   ///< YUV 4:4:4 格式
};

/**
 * @brief 帧处理类
 *
 * 提供帧数据的基本接口，包括尺寸、格式和数据访问。
 * 用于视频处理和图像帧管理。
 */
class Frame {
   public:
    /**
     * @brief 默认构造函数
     */
    Frame() = default;

    /**
     * @brief 虚析构函数
     */
    virtual ~Frame() = default;

   public:
    /**
     * @brief 获取帧宽度
     * @return size_t 帧宽度（像素）
     * @note 纯虚函数，必须在子类中实现
     */
    virtual size_t width() = 0;

    /**
     * @brief 获取帧高度
     * @return size_t 帧高度（像素）
     * @note 纯虚函数，必须在子类中实现
     */
    virtual size_t height() = 0;

    /**
     * @brief 获取颜色格式
     * @return ColorFormat 颜色格式枚举值
     * @note 纯虚函数，必须在子类中实现
     */
    virtual ColorFormat color_format() = 0;

    /**
     * @brief 获取帧数据指针
     * @return void* 帧数据原始指针
     * @note 纯虚函数，必须在子类中实现
     */
    virtual void* data() = 0;

    /**
     * @brief 获取帧数据大小
     * @return size_t 帧数据大小（字节）
     * @note 纯虚函数，必须在子类中实现
     */
    virtual size_t size() = 0;
};
}  // namespace xcal::camera
