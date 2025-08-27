# xcal 项目贡献指南

欢迎参与 xcal 项目的开发！xcal 是一个 C++ 图形渲染库，本文档将指导您如何为项目做出贡献。

## 目录
- [开发环境设置](#开发环境设置)
- [构建指南](#构建指南)
- [代码风格](#代码风格)
- [提交贡献流程](#提交贡献流程)
- [测试要求](#测试要求)
- [文档要求](#文档要求)
- [问题报告](#问题报告)

## 开发环境设置

### 编译器要求
- **编译器**: Clang-cl 19.1.0
- **C++标准**: C++23
- **构建系统**: CMake 3.15+

## 构建指南

### 使用 CMake 预设
项目提供了预配置的 CMake 预设：

```bash
# 配置项目 (Debug 模式)
cmake --preset build-debug

# 配置项目 (Release 模式)  
cmake --preset build-release

# 构建项目
cmake --build --preset build-debug
```

### 可用预设
- `build-debug`: Debug 构建配置
- `build-release`: Release 构建配置
- `clang-cl-build`: 基础 Clang-cl 配置

### 运行测试
```bash
# 构建测试
cmake --build --preset build-debug --target test_opengl

# 运行测试
./build-debug/tests/test_opengl

# 运行场景测试
./build-debug/tests/scene/scene_test
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
- **函数名**: camelCase (如 `calculatePosition`, `renderScene`) 
- **变量名**: snake_case (如 `position_list`, `color_value`)
- **常量名**: UPPER_SNAKE_CASE (如 `MAX_OBJECTS`, `DEFAULT_COLOR`)

### 头文件组织
- 使用 `#pragma once` 防止重复包含
- 头文件按功能模块组织在相应目录中
- 公共接口放在 `src/public.h` 中

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

*最后更新: 2025-08-27*
