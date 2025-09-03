# xcal 项目 AI 贡献者指南

欢迎 AI 贡献者参与 xcal 项目的开发！本文档专门为 AI 贡献者设计，提供针对性的贡献指导和最佳实践。

**重要提示**: AI 贡献者必须在每次任务开始前读取本指南，并在任务完成后更新本指南。

## 📋 开始任务前必读

在开始任何贡献任务前，请确保：

1. ✅ 完整阅读本指南
2. ✅ 理解项目架构和代码规范
3. ✅ 确认任务要求和范围
4. ✅ 检查相关测试要求

## 🏗️ 项目架构理解

### 项目概述
xcal 是一个基于 C++23 的现代图形渲染引擎，专注于提供高性能的 2D/3D 图形渲染能力。项目采用模块化设计，具有清晰的层次结构和强大的扩展性。

**核心目标**:
- 提供简洁易用的图形对象 API
- 支持多种图形渲染后端
- 实现高效的场景管理和属性系统
- 确保代码质量和测试覆盖率

### 核心模块
- **mobject**: 图形对象模块（核心抽象）
- **scene**: 场景管理模块  
- **render**: 渲染引擎模块（OpenGL/GLFW）
- **property**: 属性系统（位置、颜色、标量、时间、向量等）
- **camera**: 相机系统（正交相机、透视相机）
- **animation**: 动画系统模块（新增）

### 文件结构详解

#### 根目录文件
- `CMakeLists.txt` - 主构建配置文件，定义项目设置和依赖
- `CMakePresets.json` - CMake 预设配置
- `.clang-format` - 代码格式化配置
- `CONTRIBUTING.md` - 传统贡献指南
- `CHAT_CONTRIBUTING.md` - AI 贡献者专用指南
- `.gitignore` - Git 忽略文件配置
- `Doxyfile` - Doxygen 配置文件，用于生成项目文档
- `doxygen-dark-theme.css` - Doxygen 黑暗主题样式表

#### 资源文件
- `res/line.fs` - 线条片段着色器
- `res/line.vs` - 线条顶点着色器

#### xcal/ 源代码目录
**核心头文件**:
- `public.h` - 公共头文件，定义基础类型和日志配置
- `main.cc` - 应用程序入口点

**animation/ 动画系统模块**:
- `core/abs_animation.hpp` - 抽象动画基类，提供动画基础功能

**camera/ 相机系统**:
- `orthocamera.hpp` - 正交相机
- `perspectivecamera.cc/.hpp` - 透视相机实现
- `core/abs_camera.cc/.hpp` - 抽象相机基类
- `core/frame.hpp` - 帧处理

**mobject/ 图形对象模块**:
- `mobject_all.hpp` - 所有 mobject 头文件的聚合
- `mobject.hpp` - 基础图形对象头文件

**mobject/core/ 核心抽象**:
- `abs_mobject.hpp` - 抽象图形对象基类
- `mobject.hpp` - 基础图形对象实现
- `mobject_types.hpp` - 对象类型定义

**mobject/objects/ 具体图形对象**:
- `circle.hpp` - 圆形对象
- `rectangle.hpp` - 矩形对象  
- `line.hpp` - 线条对象
- `polygone.hpp` - 多边形对象
- `ellipse.hpp` - 椭圆对象
- `path.hpp` - 路径对象

**property/ 属性系统**:
- `color.cc/.hpp` - 颜色属性实现
- `position.hpp` - 位置属性
- `position_list.hpp` - 位置列表属性
- `scalar.hpp` - 标量属性
- `time_duration.hpp` - 时间段属性
- `time_point.hpp` - 时间点属性
- `vec.hpp` - 向量属性
- `core/property.hpp` - 属性基类定义

**scene/ 场景管理**:
- `scene.hpp` - 场景接口
- `core/abs_scene.hpp` - 抽象场景模板
- `core/scene.hpp` - 具体场景实现

**render/ 渲染引擎**:
- `core/abs_render.cc/.hpp` - 抽象渲染器基类实现
- `core/render.hpp` - 具体渲染器实现
- `impl/opengl/` - OpenGL 渲染实现
  - `opengl_render.cc/.hpp` - OpenGL 渲染器
  - `core/typedef.hpp` - 类型定义
  - `gl/` - OpenGL 底层封装
    - `buffer.cc/.hpp` - 缓冲区管理
    - `shader.cc/.hpp` - 着色器管理
    - `shaderprogram.cc/.hpp` - 着色器程序管理
    - `vertexarrayobject.cc/.hpp` - 顶点数组对象管理
  - `object/` - 图形对象渲染
    - `circle.cc/.hpp` - 圆形对象渲染
    - `line.cc/.hpp` - 线条对象渲染
    - `object.cc/.hpp` - 基础对象渲染
  - `utils/` - 工具类
    - `glfwdarkheadersupport.inc` - 暗色标题栏支持
    - `openglapiloadhelper.inc` - OpenGL API 加载助手
    - `shaderinstence.hpp` - 着色器实例管理
    - `singlemobjectwrapper.cc/.hpp` - 单对象包装器

**threed/ 3D 功能**:
- (预留模块，当前为空)

**utils/ 工具类**:
- `logmacrohelper.inc` - 日志宏助手

#### third_party/ 第三方依赖
**xclogger/ 日志库**:
- 提供异步日志提交功能
- 支持 ZMQ 和流式日志输出
- 包含日志消息处理和配置

**xcmath/ 数学库**:
- 提供数学运算、向量、矩阵、四元数等数学功能
- 符号系统支持表达式处理
- 图形数学对象支持

#### tests/ 测试目录
**模块测试**:
- `mobject/test_circle.cc` - 圆形对象测试
- `mobject/test_mobject.cc` - 基础图形对象测试
- `properties/test_color.cc` - 颜色属性测试
- `properties/test_time_duration.cc` - 时间段测试
- `properties/test_time_point.cc` - 时间点测试
- `scene/test_scene.cc` - 场景管理测试
- `camera/test_perspective_camera.cc` - 透视相机测试

**集成测试**:
- `opengl.cc` - OpenGL 渲染测试

#### tools/ 工具脚本
- `format-code.ps1` - Windows 代码格式化脚本
- `format-code.sh` - Linux/macOS 代码格式化脚本

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

### 动画系统架构
```
AbsAnimation (抽象动画基类)
  ├── 提供动画基础功能
  ├── 支持播放控制（开始、暂停、恢复、停止）
  ├── 时间管理和更新机制
  └── 可扩展的具体动画实现
```

### 场景管理系统
```
AbsScene<T> (模板抽象场景)
  └── Scene (具体场景，管理 MObject 对象)
```

### 渲染系统架构  
```
AbsRender<T> (模板抽象渲染器)
  └── (具体渲染器实现，连接 OpenGL/GLFW)
```

### 相机系统架构
```
AbsCamera (抽象相机基类)
  ├── OrthoCamera (正交相机)
  └── PerspectiveCamera (透视相机)
```

### 关键技术栈
- **编译器**: 
  - Windows: Clang-cl 19.1.0
  - Linux: Clang 19.1+
- **C++标准**: C++23
- **图形库**: OpenGL + GLFW
- **构建系统**: CMake 3.15+
- **测试框架**: GTest
- **日志系统**: xclogger (ZMQ 异步日志)

## 📝 文件操作更新规范

### 添加新文件时的更新要求
当添加新文件时，必须更新本指南的文件结构描述部分：

1. **头文件(.hpp/.h)**: 在对应的模块部分添加文件描述
2. **实现文件(.cc/.cpp)**: 在对应的模块部分添加文件描述  
3. **测试文件**: 在 tests/ 对应模块部分添加测试文件描述
4. **工具脚本**: 在 tools/ 部分添加脚本描述

**添加文件更新模板**:
```markdown
### 新增文件 - YYYY-MM-DD
- [模块名]: 添加了 `文件名` - [功能描述]
- 文件位置: `路径/文件名`
- 主要功能: [详细功能说明]
- 相关测试: [测试文件链接]
```

### 修改现有文件时的更新要求
当修改现有文件时，需要更新对应的文件描述：

1. **功能变更**: 更新文件的功能描述
2. **接口变更**: 更新接口说明和示例
3. **重大修改**: 在更新记录中添加修改说明

**修改文件更新模板**:
```markdown
### 文件修改 - YYYY-MM-DD
- [模块名]: 修改了 `文件名` - [修改内容摘要]
- 修改类型: [功能增强/ bug 修复/ 性能优化/ 重构]
- 具体变更: [详细的变更描述]
- 影响范围: [受影响的模块和功能]
```

### 删除文件时的更新要求
当删除文件时，需要从文件结构中移除对应的描述：

1. **移除文件引用**: 删除对应的文件描述
2. **说明删除原因**: 在更新记录中添加删除说明
3. **替代方案**: 如果有替代文件，需要说明

**删除文件更新模板**:
```markdown
### 文件删除 - YYYY-MM-DD
- [模块名]: 删除了 `文件名` - [删除原因]
- 原功能: [原文件的功能描述]
- 替代方案: [新的实现方式或替代文件]
- 迁移说明: [如果需要迁移，提供迁移指南]
```

### 文件命名规范
- **头文件**: 使用 `.hpp` 扩展名，小写蛇形命名
- **实现文件**: 使用 `.cc` 扩展名，小写蛇形命名  
- **测试文件**: `test_模块名_功能名.cc` 格式
- **配置文件**: 使用相应格式的扩展名

## 🎯 代码贡献规范

### 代码格式化
```bash
# 必须运行代码格式化
cmake --build build --target format-code
```

### 命名约定（严格遵循）
- **类名**: PascalCase (`MObject`, `Scene`)
- **函数名**: snake_case (`set_stroke_color`, `rotate`)
- **变量名**: snake_case (`position_list`, `color_value`)
- **常量名**: UPPER_SNAKE_CASE (`MAX_OBJECTS`, `DEFAULT_COLOR`)
- **编译期常量**: kPascalCase (`kEpsilon`, `kTypeName`)

### 头文件规范
```cpp
#pragma once  // 必须使用

#include <xcal/public.h>
#include <memory>
#include <xcal/mobject/core/abs_mobject.hpp>

namespace xcal::mobject {
class YourClass : public BaseClass {
   // 类实现
};
}  // namespace xcal::mobject
```

### 注释要求（Doxygen 格式）
```cpp
/**
 * @brief 功能描述
 * @param param1 参数说明
 * @param param2 参数说明  
 * @return 返回值说明
 * @note 注意事项
 */
float_t calculateDistance(const Position& p1, const Position& p2);
```

## 🧪 测试要求

### 单元测试（必须编写）
- 测试文件位置: `tests/` 目录
- 覆盖率要求: ≥80%
- 测试命名: `TestFeatureName.TestCaseName`

### 测试示例
```cpp
#include <gtest/gtest.h>
#include <xcal/mobject/objects/circle.hpp>

TEST(TestCircle, CreateAndValidate) {
    auto circle = std::make_unique<Circle>(Position{0, 0}, 5.0f);
    EXPECT_EQ(circle->radius(), 5.0f);
    EXPECT_EQ(circle->pos().x(), 0.0f);
}
```

### 运行测试
```bash
# 构建测试
cmake --build build --target test_opengl

# 运行特定测试
./build-debug/tests/test_opengl --gtest_filter="TestCircle.*"

# 使用 CTest 运行所有测试（需要先构建测试）
ctest --test-dir build/debug --output-on-failure

# 使用 CTest 运行特定测试
ctest --test-dir build/debug -R test_mobject --output-on-failure

# 使用 CTest 查看测试列表
ctest --test-dir build/debug -N

# 使用 CTest 并行运行测试
ctest --test-dir build/debug -j4 --output-on-failure

# 构建所有测试目标
cmake --build build --target test_mobject test_properties test_scene test_opengl test_camera
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

## 🔧 构建和验证

### CMake 预设使用
```bash
# Debug 构建
cmake -B build/debug -S . --preset build-debug
cmake --build build/debug

# Release 构建  
cmake -B build/release -S . --preset build-release
cmake --build build/release
```

### 验证步骤
1. 代码格式化检查
2. 编译通过
3. 测试全部通过
4. 功能验证

## 📝 提交规范

### Git 工作流
```bash
# 创建功能分支
git checkout -b feature/ai-your-feature-name

# 提交信息格式
git commit -m "feat(mobject): add ai-enhanced circle rendering"

# 推送到分支
git push origin feature/ai-your-feature-name
```

### 提交信息约定
- `feat`: 新功能（AI 增强）
- `fix`: bug 修复  
- `docs`: 文档更新
- `test`: 测试相关
- `refactor`: 代码重构

## 🤖 AI 最佳实践

### 代码生成原则
1. **保持一致性**: 遵循现有代码模式和风格
2. **模块化设计**: 新的功能应该易于扩展和维护
3. **性能意识**: 图形渲染代码需要高效
4. **错误处理**: 合理的异常处理和日志记录

### 避免的陷阱
- ❌ 破坏现有接口
- ❌ 忽略向后兼容性  
- ❌ 重复造轮子（优先使用现有组件）
- ❌ 忽略测试覆盖率

### 推荐模式
- ✅ 使用智能指针管理资源
- ✅ 遵循 RAII 原则
- ✅ 使用 const 正确性
- ✅ 提供清晰的接口文档

## 🔄 任务完成后更新指南

每次完成任务后，必须更新本指南：

1. **记录经验**: 添加新的最佳实践或教训
2. **更新示例**: 补充有价值的代码示例
3. **修正错误**: 修正指南中的不准确信息
4. **版本管理**: 更新版本号和日期

### 更新模板
```markdown
## 📅 更新记录 - YYYY-MM-DD

### 新增内容
- [描述新增的最佳实践或经验]

### 修正内容  
- [描述修正的错误或改进]

### 示例更新
- [添加新的代码示例或模式]
```

## 🆘 遇到问题？

1. 首先检查本指南和相关文档
2. 查看现有代码和测试用例
3. 运行代码格式化工具检查风格
4. 确保所有测试通过

## 📅 更新记录 - 2025-09-04

### 新增内容
- 添加了动画系统模块文档，包括抽象动画基类实现
- 更新了完整的文件结构以反映当前项目状态
- 添加了相机系统测试文件说明
- 完善了属性系统架构，添加向量属性支持

### 修正内容  
- 修正了所有目录结构引用（从 `src/` 改为 `xcal/`）
- 更新了核心模块列表，添加了 animation 模块
- 修正了文件路径描述，确保与实际结构一致
- 更新了测试运行命令格式

### 示例更新
- 添加了动画系统架构说明
- 更新了相机系统架构文档
- 添加了透视相机测试文件说明

### 新增最佳实践
- **动画系统设计**: 提供抽象动画基类，支持播放控制和时间管理
- **文件结构管理**: 确保文档与实际项目结构保持同步
- **测试覆盖率**: 为所有新增功能编写相应的测试用例

## 📅 更新记录 - 2025-09-02

### 新增内容
- 添加了相机系统模块文档，包括正交相机和透视相机实现
- 完善了渲染引擎的 OpenGL 实现详细文档
- 添加了第三方 xcmath 数学库依赖说明
- 更新了属性系统文档，包括向量属性支持

### 修正内容  
- 修正了源代码目录结构描述（从 `src/` 改为 `xcal/`）
- 更新了文件结构以反映实际项目布局
- 修正了核心模块列表，添加了 camera 模块

### 示例更新
- 添加了透视相机测试文件说明
- 更新了 OpenGL 渲染实现的详细文件结构

### 新增最佳实践
- **相机系统设计**: 支持正交和透视相机，提供抽象相机基类
- **OpenGL 渲染优化**: 使用 glbinding 替代 glad，提供更好的类型安全
- **数学库集成**: 集成 xcmath 库提供数学运算支持
- **构建系统改进**: 支持更灵活的 CMake 预设配置

## 📅 更新记录 - 2025-08-27

### 新增内容
- 添加了详细的 Doxygen 注释编写最佳实践示例
- 补充了完整的单元测试编写模式和示例
- 添加了时间属性（TimeDuration 和 TimePoint）的实现和测试最佳实践
- **添加了完整的项目概述和文件结构详细描述**
- **完善了文件操作更新机制和规范**

### 修正内容
- 更新了测试运行命令的正确格式（Windows 路径格式)
- 修正了测试示例中的属性访问方法
- 解决了构造函数歧义问题（移除 size_t 构造函数，使用设置方法）

### 示例更新
- 添加了完整的 Circle 类测试示例
- 添加了 Color 属性类测试示例  
- 添加了 Scene 场景管理测试示例
- 添加了 TimeDuration 时间段属性测试示例
- 添加了 TimePoint 时间点属性测试示例

### 新增最佳实践
- **时间属性设计**: 使用微秒精度存储时间值，提供浮点数秒接口
- **构造函数设计**: 避免构造函数歧义，优先使用设置方法
- **时间运算**: 支持时间段和时间点的各种算术和比较运算
- **精度处理**: 正确处理浮点数到整数的转换精度
- **文件操作规范**: 添加、修改、删除文件时的文档更新要求

## 📊 版本历史

- **v1.5.0** (2025-09-04): 添加动画系统模块，全面更新文件结构文档
- **v1.4.0** (2025-09-02): 根据项目变更更新文件结构和模块文档
- **v1.3.0** (2025-08-27): 添加 CTest 支持，完善测试运行机制
- **v1.2.0** (2025-08-27): 添加项目概述和文件结构详细描述，完善文件操作更新机制
- **v1.1.0** (2025-08-27): 添加注释和测试最佳实践，更新测试示例
- **v1.0.1** (2025-08-27): 根据用户反馈添加任务前后阅读和更新要求
- **v1.0.0** (2025-08-27): 初始版本，基于 CONTRIBUTING.md 和项目分析创建

---

*最后更新: 2025-09-04*  
*AI 贡献者请在每次任务开始前读取本指南，并在任务完成后更新本指南*
