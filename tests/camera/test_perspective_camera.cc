#include <gtest/gtest.h>

#include <cmath>
#include <xcal/camera/core/perspectivecamera.hpp>

/**
 * @brief PerspectiveCamera 测试套件
 *
 * 测试 PerspectiveCamera 类的创建、矩阵计算和属性管理功能。
 */
namespace xcal::camera {

/**
 * @brief 测试默认构造函数
 */
TEST(TestPerspectiveCamera, CreateWithDefaultValues) {
    auto camera =
        std::make_unique<PerspectiveCamera>(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);

    // 验证初始值
    EXPECT_FLOAT_EQ(camera->fov().value(), 60.0f);
    EXPECT_FLOAT_EQ(camera->aspect().value(), 16.0f / 9.0f);
    EXPECT_FLOAT_EQ(camera->near().value(), 0.1f);
    EXPECT_FLOAT_EQ(camera->far().value(), 100.0f);

    // 验证默认位置和方向
    EXPECT_FLOAT_EQ(camera->position().value()[0], 0.0f);
    EXPECT_FLOAT_EQ(camera->position().value()[1], 0.0f);
    EXPECT_FLOAT_EQ(camera->position().value()[2], -1.0f);

    EXPECT_FLOAT_EQ(camera->target().value()[0], 0.0f);
    EXPECT_FLOAT_EQ(camera->target().value()[1], 0.0f);
    EXPECT_FLOAT_EQ(camera->target().value()[2], 0.0f);

    EXPECT_FLOAT_EQ(camera->up().value()[0], 0.0f);
    EXPECT_FLOAT_EQ(camera->up().value()[1], 1.0f);
    EXPECT_FLOAT_EQ(camera->up().value()[2], 0.0f);
}

/**
 * @brief 测试自定义参数构造函数
 */
TEST(TestPerspectiveCamera, CreateWithCustomValues) {
    auto camera =
        std::make_unique<PerspectiveCamera>(45.0f, 4.0f / 3.0f, 1.0f, 1000.0f);

    EXPECT_FLOAT_EQ(camera->fov().value(), 45.0f);
    EXPECT_FLOAT_EQ(camera->aspect().value(), 4.0f / 3.0f);
    EXPECT_FLOAT_EQ(camera->near().value(), 1.0f);
    EXPECT_FLOAT_EQ(camera->far().value(), 1000.0f);
}

/**
 * @brief 测试投影矩阵计算
 */
TEST(TestPerspectiveCamera, ProjectionMatrixCalculation) {
    auto camera =
        std::make_unique<PerspectiveCamera>(90.0f, 1.0f, 0.1f, 100.0f);

    // 获取投影矩阵
    const auto& P = camera->projection_matrix();

    // 验证矩阵的基本属性
    EXPECT_NE(P[0][0], 0.0f);
    EXPECT_NE(P[1][1], 0.0f);
    EXPECT_NE(P[2][2], 0.0f);
    EXPECT_NE(P[3][2], 0.0f);
    EXPECT_EQ(P[2][3], -1.0f);

    // 验证透视投影矩阵的特定值
    // 对于 90° FOV, aspect=1, near=0.1, far=100
    float expected_f = 1.0f / tan(90.0f * 3.14159265358979323846f / 360.0f);
    EXPECT_NEAR(P[0][0], expected_f, 1e-5f);
    EXPECT_NEAR(P[1][1], expected_f, 1e-5f);
}

/**
 * @brief 测试视图矩阵计算 - 标准look-at
 */
TEST(TestPerspectiveCamera, ViewMatrixLookAt) {
    auto camera =
        std::make_unique<PerspectiveCamera>(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);

    // 设置标准相机位置和方向
    camera->position().value() = {0.0f, 0.0f, -5.0f};
    camera->target().value() = {0.0f, 0.0f, 0.0f};
    camera->up().value() = {0.0f, 1.0f, 0.0f};

    // 获取视图矩阵
    const auto& V = camera->view_matrix();

    // 验证视图矩阵的基本属性
    // 对于标准look-at，Z轴应该指向相机前方
    EXPECT_NEAR(V[0][2], 0.0f, 1e-5f);
}
}  // namespace xcal::camera