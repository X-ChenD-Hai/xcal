#!/bin/sh
# 从命令行参数获取 clang-format 路径和源码根目录
clang_format_path="$1"
source_path="$2"

# 参数检查
[ -z "$clang_format_path" ] && {
    echo "No clang-format path specified." >&2
    exit 1
}
[ -z "$source_path" ] && {
    echo "No source path specified." >&2
    exit 1
}

# 统一分隔符（把反斜杠换成正斜杠，防止 Windows 路径问题）
source_path=$(printf '%s\n' "$source_path" | sed 's|\\|/|g')

echo "clang-format path: $clang_format_path"
echo "source path: $source_path"

# 要扫描的目录列表
for dir in src tests; do
    search_dirs="$search_dirs $source_path/$dir"
done

# 查找所有匹配文件
# shellcheck disable=SC2086   # 故意展开变量
files=$(find $search_dirs -type f \( \
    -name '*.h' -o \
    -name '*.hpp' -o \
    -name '*.cc' -o \
    -name '*.cpp' \
\) 2>/dev/null)

# 逐个格式化
for f in $files; do
    rel_path=${f#$source_path/}
    echo "Formatting $rel_path ..."
    "$clang_format_path" -i "$f"
done