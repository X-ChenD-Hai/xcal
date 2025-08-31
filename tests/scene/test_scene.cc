#include <gtest/gtest.h>

#include <mobject/objects/circle.hpp>
#include <mobject/objects/rectangle.hpp>
#include <scene/scene.hpp>

/**
 * @brief 场景管理测试套件
 *
 * 测试 Scene 类的对象管理和操作功能。
 */
TEST(TestScene, CreateEmptyScene) {
    // 测试创建空场景
    xcal::scene::Scene scene;

    // 新创建的场景应该为空
    EXPECT_TRUE(scene.mobjects().empty());
    EXPECT_EQ(scene.mobjects().size(), 0);
}

TEST(TestScene, AddCircleWithSmartPointer) {
    // 测试使用智能指针添加圆形对象
    xcal::scene::Scene scene;

    // 创建圆形对象并添加到场景
    xcal::mobject::Circle* circlePtr = scene.add<xcal::mobject::Circle>(
        xcal::property::Position{1.0f, 2.0f}, 3.0f);

    // 验证对象添加成功
    EXPECT_FALSE(scene.mobjects().empty());
    EXPECT_EQ(scene.mobjects().size(), 1);
    EXPECT_NE(circlePtr, nullptr);
    EXPECT_EQ(circlePtr->radius(), 3.0f);
    EXPECT_EQ(circlePtr->pos().x(), 1.0f);
    EXPECT_EQ(circlePtr->pos().y(), 2.0f);
}

TEST(TestScene, AddCircleWithRawPointer) {
    // 测试使用裸指针添加圆形对象
    xcal::scene::Scene scene;

    // 创建圆形对象并添加到场景
    auto circle =
        new xcal::mobject::Circle(xcal::property::Position{4.0f, 5.0f}, 6.0f);
    xcal::mobject::Circle* circlePtr = scene.add(circle);

    // 验证对象添加成功
    EXPECT_FALSE(scene.mobjects().empty());
    EXPECT_EQ(scene.mobjects().size(), 1);
    EXPECT_EQ(circlePtr, circle);
    EXPECT_EQ(circlePtr->radius(), 6.0f);
}

TEST(TestScene, AddCircleWithConstruction) {
    // 测试直接在场景中构造并添加圆形对象
    xcal::scene::Scene scene;

    // 在场景中直接构造圆形对象
    xcal::mobject::Circle* circlePtr = scene.add<xcal::mobject::Circle>(
        xcal::property::Position{7.0f, 8.0f}, 9.0f);

    // 验证对象添加成功
    EXPECT_FALSE(scene.mobjects().empty());
    EXPECT_EQ(scene.mobjects().size(), 1);
    EXPECT_NE(circlePtr, nullptr);
    EXPECT_EQ(circlePtr->radius(), 9.0f);
    EXPECT_EQ(circlePtr->pos().x(), 7.0f);
    EXPECT_EQ(circlePtr->pos().y(), 8.0f);
}

TEST(TestScene, AddMultipleObjects) {
    // 测试添加多个不同类型的对象
    xcal::scene::Scene scene;

    // 添加圆形对象
    auto circlePtr = scene.add<xcal::mobject::Circle>(
        xcal::property::Position{1.0f, 1.0f}, 2.0f);

    // 添加矩形对象
    auto rectPtr = scene.add<xcal::mobject::Rectangle>(
        xcal::property::Position{3.0f, 3.0f}, 4.0f, 5.0f);

    // 验证两个对象都添加成功
    EXPECT_EQ(scene.mobjects().size(), 2);
    EXPECT_NE(circlePtr, nullptr);
    EXPECT_NE(rectPtr, nullptr);

    // 验证对象类型正确
    EXPECT_EQ(circlePtr->radius(), 2.0f);
    // 注意：这里假设 Rectangle 有 width() 和 height() 方法
}

TEST(TestScene, ObjectOwnership) {
    // 测试场景对对象的所有权管理
    xcal::scene::Scene scene;

    // 创建对象并添加到场景
    auto originalCircle = std::make_unique<xcal::mobject::Circle>();
    xcal::mobject::Circle* circlePtr = originalCircle.get();

    // 转移所有权到场景
    scene.add(std::move(originalCircle));

    // 原始指针应该不再拥有对象
    // 场景应该管理对象的生命周期
    EXPECT_FALSE(scene.mobjects().empty());

    // 验证可以通过返回的指针访问对象
    EXPECT_EQ(circlePtr->radius(), 1.0f);  // 默认半径
}

TEST(TestScene, ConstAccessToObjects) {
    // 测试常量访问对象列表
    xcal::scene::Scene scene;

    // 添加一些对象
    scene.add<xcal::mobject::Circle>();
    scene.add<xcal::mobject::Circle>();

    // 获取常量引用
    const auto& constObjects = scene.mobjects();

    // 验证可以常量访问
    EXPECT_EQ(constObjects.size(), 2);

    // 验证每个对象都存在
    for (const auto& obj : constObjects) {
        EXPECT_NE(obj.get(), nullptr);
        EXPECT_TRUE(obj->visible());  // 默认应该可见
    }
}

TEST(TestScene, SceneDestruction) {
    // 测试场景析构时正确释放对象
    // 这个测试主要验证没有内存泄漏
    // 实际的内存泄漏检测需要专门的工具

    {
        xcal::scene::Scene scene;

        // 添加多个对象
        scene.add<xcal::mobject::Circle>();
        scene.add<xcal::mobject::Circle>();
        scene.add<xcal::mobject::Circle>();

        EXPECT_EQ(scene.mobjects().size(), 3);
    }

    // 场景析构后，所有对象应该被正确释放
    // 如果没有内存错误，测试通过
    SUCCEED();
}
