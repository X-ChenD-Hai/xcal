#include <sol/sol.hpp>

#include "sol/state.hpp"

int main() {
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.set_function("myprint",
                     [](const std::string& s) { std::cout << s << std::endl; });
    lua.script_file("tests/lua/script.lua");
    return 0;
}