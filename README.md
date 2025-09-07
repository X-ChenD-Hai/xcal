# xcal - 现代 C++ 图形渲染引擎

xcal 是一个基于 C++23 的高性能图形渲染引擎，专注于提供简洁易用的 2D/3D 图形渲染能力。项目采用模块化设计，具有清晰的架构和强大的扩展性。

## ✨ 特性

- **现代 C++23**: 使用最新的 C++ 标准，确保代码质量和性能
- **模块化设计**: 清晰的模块划分，易于扩展和维护
- **多种图形对象**: 支持圆形、矩形、线条、多边形、椭圆、路径等
- **完整的属性系统**: 位置、颜色、标量、时间、向量等属性支持
- **场景管理**: 高效的场景对象管理和渲染
- **相机系统**: 支持正交相机和透视相机
- **动画系统**: 提供基础的动画功能支持
- **OpenGL 渲染**: 基于 OpenGL/GLFW 的高性能渲染后端
- **跨平台构建**: 使用 CMake 构建系统，支持 Windows、Linux、macOS

## 🚀 快速开始

### 系统要求

- **编译器**: 
  - Windows: Clang-cl 19.1.0
  - Linux: Clang 19.1+
- **CMake**: 3.15 或更高版本
- **图形库**: OpenGL 3.3+ 和 GLFW

### 依赖项

- **GLFW3**: 窗口管理和 OpenGL 上下文创建
- **渲染后端** (二选一):
  - **glbinding**: OpenGL 函数绑定库
  - **glad**: OpenGL 函数加载库
- **ZeroMQ**: 异步日志支持 (通过 cppzmq)
- **JSON**: 日志消息格式化 (通过 nlohmann_json)
- **xcmath**: 内部数学运算库
- **xclogger**: 内部日志系统

### 安装和构建

```bash
# 克隆项目
git clone https://github.com/X-ChenD-Hai/xcal-next.git
cd xcal-next

# 配置项目 (Debug 模式)
cmake -B build/debug -S . --preset build-debug

# 构建项目
cmake --build build/debug

# 运行示例
./build/debug/xcal/xcal
```

### 使用示例

基于 `main.cc` 的简单使用示例：

```cpp
#include <xcal/public.h>
#include <memory>
#include <xcal/camera/perspectivecamera.hpp>
#include <xcal/mobject/mobject_all.hpp>
#include <xcal/mobject/objects/circle.hpp>
#include <xcal/render/impl/opengl/opengl_render.hpp>

int main(int argc, char **argv) {
    XCAL_INFO(XCAL, APP) << "应用程序启动";
    
    // 创建场景
    auto scene = std::make_unique<xcal::scene::Scene>();
    using namespace xcal::mobject;
    using namespace xcal::camera;

    // 添加图形对象
    scene->add<Circle>()->set_stroke_color({0, 0.5, 0.5});
    scene->add<Line>(2)->set_stroke_color({1, 0, 0});
    scene->add<Line>(2)->set_stroke_color({0, 1, 0})->rotate(90);
    
    // 添加透视相机
    scene->add(std::make_unique<PerspectiveCamera>(45.0, 16 / 9.0, 0.1, 1000.0))
        ->set_position(0, 0, 5)->set_target(0, 0.5, 0);
    
    // 创建渲染器并显示
    auto render = xcal::render::opengl::OpenGLRender{scene.get()};
    render.show();
    
    XCAL_INFO(XCAL, APP) << "应用程序结束";
    return 0;
}
```

## 📖 文档

详细的 API 文档已部署在 GitHub Pages 上：

- **在线文档**: [https://x-chend-hai.github.io/xcal/](https://x-chend-hai.github.io/xcal/)

文档包含完整的类参考、模块说明和使用示例，采用黑暗主题设计，提供更好的阅读体验。

## 📁 项目结构

```
xcal/
├── xcal/                 # 源代码目录
│   ├── animation/        # 动画系统模块
│   ├── camera/           # 相机系统模块
│   ├── mobject/          # 图形对象模块
│   ├── property/         # 属性系统模块
│   ├── render/           # 渲染引擎模块
│   ├── scene/            # 场景管理模块
│   ├── public.h          # 公共头文件
│   └── main.cc           # 应用程序入口点
├── tests/                # 测试目录
├── third_party/          # 第三方依赖
├── res/                  # 资源文件
├── tools/                # 工具脚本
└── CMakeLists.txt        # 主构建配置
```

## 🧪 测试

项目包含完整的单元测试和集成测试：

```bash
# 构建所有测试
cmake --build build/debug --target test_mobject test_properties test_scene test_opengl test_camera

# 运行所有测试
ctest --test-dir build/debug --output-on-failure

# 运行特定测试
ctest --test-dir build/debug -R test_mobject --output-on-failure
```

## 🔧 开发指南

### 代码风格

项目使用 `.clang-format` 进行代码格式化：

```bash
# 格式化代码
cmake --build build --target format-code
```

### 命名约定

- **类名**: PascalCase (`MObject`, `Scene`)
- **函数名**: snake_case (`add_object`, `set_position`)
- **变量名**: snake_case (`position_list`, `color_value`)
- **常量名**: UPPER_SNAKE_CASE (`MAX_OBJECTS`, `DEFAULT_COLOR`)

### 注释规范

使用 Doxygen 格式注释：

```cpp
/**
 * @brief 计算两个点的距离
 * @param p1 第一个点
 * @param p2 第二个点  
 * @return 两点之间的欧几里得距离
 */
float_t calculateDistance(const Position& p1, const Position& p2);
```

## 🤝 贡献指南

我们欢迎贡献！请参阅详细的贡献指南：

- [CONTRIBUTING.md](CONTRIBUTING.md) - 传统贡献指南
- [CHAT_CONTRIBUTING.md](CHAT_CONTRIBUTING.md) - AI 贡献者专用指南

### 提交规范

使用约定式提交格式：

- `feat`: 新功能
- `fix`: bug 修复
- `docs`: 文档更新
- `test`: 测试相关
- `refactor`: 代码重构

示例: `feat(mobject): add circle object implementation`

## 📄 许可证

项目采用开源许可证，具体请查看 [LICENSE](LICENSE) 文件。

## 📞 联系方式

如有问题或建议，请通过以下方式联系：

- 创建 GitHub Issue
- 通过 Pull Request 讨论

## 🙏 致谢

感谢所有贡献者和用户的支持！

---

*最后更新: 2025-09-04*
