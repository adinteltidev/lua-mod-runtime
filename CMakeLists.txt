cmake_minimum_required(VERSION 3.16)
project(lua_mod_runtime LANGUAGES C)

file(GLOB lua_sources CONFIGURE_DEPENDS third_party/lua/*.c)
add_library(lua_mod_runtime STATIC ${lua_sources} src/mods/sandbox.c)
target_include_directories(lua_mod_runtime PUBLIC src third_party/lua)
target_compile_features(lua_mod_runtime PUBLIC c_std_99)
if(UNIX)
  target_compile_definitions(lua_mod_runtime PRIVATE LUA_USE_POSIX)
  target_link_libraries(lua_mod_runtime PUBLIC m)
endif()

add_executable(lua-mod-run src/main.c)
target_link_libraries(lua-mod-run PRIVATE lua_mod_runtime)

include(CTest)
if(BUILD_TESTING)
  add_test(NAME example COMMAND lua-mod-run "${CMAKE_CURRENT_SOURCE_DIR}/examples/basic.lua")
  add_test(NAME script_error COMMAND ${CMAKE_COMMAND}
    "-DRUNNER=$<TARGET_FILE:lua-mod-run>"
    "-DSCRIPT_PATH=${CMAKE_CURRENT_BINARY_DIR}/script-error.lua"
    [=[-DSCRIPT=error("intentional test failure")]=]
    "-DEXPECTED_ERROR=intentional test failure"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/check_cli.cmake")
  add_test(NAME execution_limit COMMAND ${CMAKE_COMMAND}
    "-DRUNNER=$<TARGET_FILE:lua-mod-run>"
    "-DSCRIPT_PATH=${CMAKE_CURRENT_BINARY_DIR}/execution-limit.lua"
    "-DSCRIPT=while true do end"
    "-DEXPECTED_ERROR=exceeded the (instruction|time) limit"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/check_cli.cmake")
endif()
