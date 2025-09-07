/**
 * @file orthocamera.hpp
 * @author X_Chen D_Hai (illuminatestar@foxmail.com)
 * @brief 正交相机类
 * @version 0.1
 * @date 2025-09-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <xcal/camera/core/abs_camera.hpp>

namespace xcal::camera {

/**
 * @brief 正交相机类
 *
 * 实现正交投影相机功能，继承自抽象相机基类。
 * 正交相机保持物体大小不变，无论距离远近。
 */
class XCAL_API OrthoCamera : public AbsCamera {};
}  // namespace xcal::camera
