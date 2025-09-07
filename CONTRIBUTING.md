# xcal 项目贡献指南

欢迎参与 xcal 项目的开发！xcal 是一个 C++ 图形渲染库，本文档将指导您如何为项目做出贡献。

## 目录
- [开发环境设置](#开发环境设置)
- [项目结构](#项目结构)
- [构建指南](#构建指南)
- [代码风格](#代码风格)
- [提交贡献流程](#提交贡献流程)
- [测试要求](#测试要求)
- [文档要求](#文档要求)
- [问题报告](#问题报告)

## 开发环境设置

### 编译器要求
- **编译器**: 
  - Windows: Clang-cl 19.1.0
  - Linux: Clang 19.1+
- **C++标准**: C++23
- **构建系统**: CMake 3.15+

### 依赖项

- **GLFW3**: 窗口管理和 OpenGL 上下文创建
- **渲染后端** (二选一):
  - **glbinding**: OpenGL 函数绑定库
  - **glad**: OpenGL 函数加载库
- **FFmpeg**: 视频编解码支持（新增）
- **ZeroMQ**: 异步日志支持 (通过 cppzmq)
- **JSON**: 日志消息格式化 (通过 nlohmann_json)
- **xcmath**: 内部数学运算库
- **xclogger**: 内部日志系统

## 项目结构

### 核心模块
- **mobject**: 图形对象模块（核心抽象）
- **scene**: 场景管理模块  
- **render**: 渲染引擎模块（OpenGL/GLFW）
- **property**: 属性系统（位置、颜色、标量、时间、向量等）
- **camera**: 相机系统（正交相机、透视相机）
- **animation**: 动画系统模块
- **codec**: 视频编解码器模块（新增）

### 文件结构
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

### 关键文件说明
- **核心头文件**: `public.h` (基础类型和日志配置), `main.cc` (应用程序入口点)
- **动画系统**: `animation/core/abs_animation.hpp` (抽象动画基类)
- **相机系统**: 正交相机、透视相机实现和抽象基类
- **图形对象**: 圆形、矩形、线条、多边形、椭圆、路径等具体对象
- **属性系统**: 位置、颜色、标量、时间、向量等属性实现
- **场景管理**: 场景接口和具体实现
- **渲染引擎**: OpenGL 渲染实现，包括缓冲区、着色器、顶点数组对象管理
- **视频编解码器**: FFmpeg 编解码器实现和抽象接口（新增）
- **工具类**: 路径处理工具（新增）
- **第三方依赖**: xclogger (日志库), xcmath (数学库), FFmpeg (视频编解码库)

### 继承结构
```
AbsMObject (抽象基类)
  └── MObject (基础图形对象)
       ├── Circle
       ├── Rectangle  
       ├── Line
       ├── Polygon
       ├── Ellipse
       └── Path
```

### 属性系统架构
```
MProperty (属性基类)
  ├── Position (位置属性)
  ├── Color (颜色属性)
  ├── Scalar (标量属性)
  ├── TimeDuration (时间段属性)
  ├── TimePoint (时间点属性)
  └── Vec (向量属性)
```

## 构建指南

### 使用 CMake 预设
项目提供了预配置的 CMake 预设：

```bash
# 配置项目 (Debug 模式)
cmake -B build/debug -S . --preset build-debug

# 配置项目 (Release 模式)  
cmake -B build/release -S . --preset build-release

# 构建项目
cmake --build build/debug
```

### 可用预设
- `build-debug`: Debug 构建配置
- `build-release`: Release 构建配置
- `clang-cl-build`: 基础 Clang-cl 配置

### 运行测试
```bash
# 构建所有测试
cmake --build build/debug --target test_mobject test_properties test_scene test_opengl test_camera

# 使用 CTest 运行所有测试
ctest --test-dir build/debug --output-on-failure

# 使用 CTest 运行特定测试
ctest --test-dir build/debug -R test_mobject --output-on-failure

# 使用 CTest 查看测试列表
ctest --test-dir build/debug -N

# 使用 CTest 并行运行测试
ctest --test-dir build/debug -j4 --output-on-failure

# 直接运行特定测试可执行文件
./build/debug/tests/test_opengl --gtest_filter="TestCircle.*"
```

**注意**: 首次启用 CTest 或添加新测试后，需要重新配置和构建项目：
```bash
# 重新配置项目
cmake -B build/debug -S . --preset build-debug

# 构建所有测试
cmake --build build/debug --target test_mobject test_properties test_scene test_opengl test_camera

# 然后就可以使用 CTest 了
ctest --test-dir build/debug --output-on-failure
```

## 代码风格

### 格式化工具
项目使用 `.clang-format` 进行代码格式化，基于 Google 风格，缩进为 4 个空格。项目提供了 CMake 目标来自动格式化代码：

```bash
cmake --build build --target format-code
```

### 命名约定
项目遵循 Google C++ 风格指南：
- **类名**: PascalCase (如 `MObject`, `Scene`)
- **函数名**: snake_case (如 `set_stroke_color`, `rotate`) 
- **变量名**: snake_case (如 `position_list`, `color_value`)
- **私有成员变量**: snake_case_
- **常量名**: UPPER_SNAKE_CASE (如 `MAX_OBJECTS`, `DEFAULT_COLOR`)
- **编译期常量名**: kPascalCase (如 `kTypeName`, `kEnumString`)

### 头文件组织
- 使用 `#pragma once` 防止重复包含
- 头文件按功能模块组织在相应目录中

## 提交贡献流程

### Git 工作流
1. Fork 本仓库
2. 创建功能分支: `git checkout -b feature/your-feature-name`
3. 提交更改: `git commit -m "feat: add your feature"`
4. 推送到分支: `git push origin feature/your-feature-name`
5. 创建 Pull Request

### 提交信息规范
使用约定式提交格式：

- `feat`: 新功能
- `fix`: bug 修复
- `docs`: 文档更新
- `style`: 代码格式调整
- `refactor`: 代码重构
- `test`: 测试相关
- `chore`: 构建过程或辅助工具变动

示例: `feat(mobject): add circle object implementation`

### Pull Request 要求
- 包含清晰的描述和修改目的
- 通过所有 CI 检查
- 包含相应的测试用例
- 更新相关文档

## 测试要求

### 单元测试
- 为所有新功能编写单元测试
- 测试文件放在 `tests/` 目录下
- 使用 GTest 框架编写测试

### 测试覆盖率
确保新代码的测试覆盖率不低于 80%

### 测试运行
```bash
# 运行所有测试
ctest --preset build-debug

# 运行特定测试
./build-debug/tests/test_opengl --gtest_filter="TestScene.*"
```

## 文档要求

### 代码注释
- 使用 Doxygen 格式注释公共接口
- 为复杂算法添加详细注释
- 保持注释与代码同步更新

示例:
```cpp
/**
 * @brief 计算两个点的距离
 * @param p1 第一个点
 * @param p2 第二个点  
 * @return 两点之间的欧几里得距离
 */
float_t calculateDistance(const Position& p1, const Position& p2);
```

### API 文档
- 所有公共类和函数都需要文档
- 文档应该说明参数、返回值和使用示例

## 问题报告

### Bug 报告
当报告 bug 时，请包含以下信息：
1. 问题描述
2. 重现步骤
3. 期望行为 vs 实际行为
4. 环境信息 (编译器版本、操作系统等)
5. 相关日志输出

### 功能请求
提出新功能时请说明：
1. 功能需求描述
2. 使用场景
3. 可能的实现方案
4. 相关参考资料

## 联系方式
如有问题，可以通过以下方式联系：
- 创建 GitHub Issue
- 通过 Pull Request 讨论

感谢您的贡献！🎉

---

*最后更新: 2025-09-07*
