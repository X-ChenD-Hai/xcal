# 从参数中获取 clang-format 的路径
$clangFormatPath = $args[0]
$sourcePath      = $args[1]

if (-not $clangFormatPath) {
    Write-Host "No clang-format path specified."
    exit 1
}
if (-not $sourcePath) {
    Write-Host "No source path specified."
    exit 1
}

# 统一分隔符
$sourcePath = $sourcePath -replace "/", "\"

Write-Output "clang-format path: $clangFormatPath"
Write-Output "source path: $sourcePath"

# 要扫描的目录
$searchDirs = @(
    Join-Path $sourcePath "xcal"
    Join-Path $sourcePath "tests"
)

# 匹配模式
$patterns = @("*.h", "*.hpp", "*.cc", "*.cpp",“*.c”,"*.inc")

# 获取文件列表
$files = Get-ChildItem -Path $searchDirs -Recurse -Include $patterns

# 格式化
foreach ($f in $files) {
    $file = $f.FullName
    $rel  = $file.Substring($sourcePath.Length + 1)
    Write-Host "Formatting $rel ..."
    & $clangFormatPath -i $file
}