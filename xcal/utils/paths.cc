#include <filesystem>
#include <string>
#include <xcal/utils/paths.hpp>

#if defined(_WIN32) || defined(_WIN64)
#    include <windows.h>
#    define GET_EXECUTABLE_PATH() getExecutablePathWindows()
static std::string getExecutablePathWindows() {
    char path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);
    return std::string(path);
}
#elif defined(__linux__)
#    include <limits.h>
#    include <unistd.h>
#    define GET_EXECUTABLE_PATH() getExecutablePathLinux()
static std::string getExecutablePathLinux() {
    char path[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len != -1) {
        path[len] = '\0';
        return std::string(path);
    }
    return "";
}
#elif defined(__APPLE__) || defined(__MACH__)
#    include <objc/objc.h>
#    include <objc/runtime.h>
#    define GET_EXECUTABLE_PATH() getExecutablePathMacOS()
static std::string getExecutablePathMacOS() {
    @autoreleasepool {
        NSString *path = [[NSBundle mainBundle] executablePath];
        return std::string([path UTF8String]);
    }
}
#else
#    error "Unsupported platform"
#endif
namespace xcal::utils::paths {
const std::string CURRENT_WORKING_DIRECTORY =
    std::filesystem::current_path().string();
const std::string EXECUTABLE_PATH = GET_EXECUTABLE_PATH();
const std::string EXECUTABLE_DIR =
    std::filesystem::is_directory(EXECUTABLE_PATH)
        ? EXECUTABLE_PATH
        : std::filesystem::path(EXECUTABLE_PATH).parent_path().string();
}  // namespace xcal::utils::paths