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

### 核心模块
- **mobject**: 图形对象模块（核心抽象）
- **scene**: 场景管理模块  
- **render**: 渲染引擎模块（OpenGL/GLFW）
- **properties**: 属性系统（位置、颜色、标量等）

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

### 关键技术栈
- **编译器**: Clang-cl 19.1.0
- **C++标准**: C++23
- **图形库**: OpenGL + GLFW
- **构建系统**: CMake 3.15+
- **测试框架**: GTest

## 🎯 代码贡献规范

### 代码格式化
```bash
# 必须运行代码格式化
cmake --build build --target format-code
```

### 命名约定（严格遵循）
- **类名**: PascalCase (`MObject`, `Scene`)
- **函数名**: camelCase (`calculatePosition`, `renderScene`)
- **变量名**: snake_case (`position_list`, `color_value`)
- **常量名**: UPPER_SNAKE_CASE (`MAX_OBJECTS`, `DEFAULT_COLOR`)

### 头文件规范
```cpp
#pragma once  // 必须使用

#include <public.h>
#include <memory>
#include <mobject/core/absmobject.hpp>

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
#include <mobject/objects/circle.hpp>

TEST(TestCircle, CreateAndValidate) {
    auto circle = std::make_unique<Circle>(Position{0, 0}, 5.0f);
    EXPECT_EQ(circle->radius(), 5.0f);
    EXPECT_EQ(circle->pos().x(), 0.0f);
}
```

### 运行测试
```bash
# 构建测试
cmake --build --preset build-debug --target test_opengl

# 运行特定测试
./build-debug/tests/test_opengl --gtest_filter="TestCircle.*"
```

## 🔧 构建和验证

### CMake 预设使用
```bash
# Debug 构建
cmake -Bbuild/debug -S. --preset build-debug
cmake --build build/debug

# Release 构建  
cmake  -Bbuild/release -S. --preset build-release
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

## 📅 更新记录 - 2025-08-27

### 新增内容
- 添加了详细的 Doxygen 注释编写最佳实践示例
- 补充了完整的单元测试编写模式和示例
- 添加了时间属性（TimeDuration 和 TimePoint）的实现和测试最佳实践

### 修正内容  
- 更新了测试运行命令的正确格式（Windows 路径格式）
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

## 📊 版本历史

- **v1.0.0** (2025-08-27): 初始版本，基于 CONTRIBUTING.md 和项目分析创建
- **v1.0.1** (2025-08-27): 根据用户反馈添加任务前后阅读和更新要求
- **v1.1.0** (2025-08-27): 添加注释和测试最佳实践，更新测试示例

---

*最后更新: 2025-08-27*  
*AI 贡献者请在每次任务开始前读取本指南，并在任务完成后更新本指南*
