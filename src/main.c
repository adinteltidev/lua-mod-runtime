#include "mods/sandbox.h"
#include "lua.h"
#include "lauxlib.h"
#include <stdio.h>
#include <stdlib.h>

static int open_libraries(lua_State *lua) {
  mod_open_libs_hardened(lua);
  return 0;
}

static int run_script(lua_State *lua, const char *path) {
  lua_pushcfunction(lua, open_libraries);
  int status = lua_pcall(lua, 0, 0, 0);
  if (status == LUA_OK) {
    status = luaL_loadfilex(lua, path, "t");
  }
  if (status == LUA_OK) {
    bool exhausted;
    bool deadline_hit;
    status = mod_resume_budgeted(lua, 0, MOD_LOAD_INSTRUCTION_BUDGET,
                                 MOD_LOAD_WALLCLOCK_DEADLINE_SECONDS,
                                 &exhausted, &deadline_hit);
    if (exhausted) {
      fputs(deadline_hit ? "Lua script exceeded the time limit.\n"
                         : "Lua script exceeded the instruction limit.\n", stderr);
      return EXIT_FAILURE;
    }
  }
  if (status != LUA_OK) {
    const char *message = lua_type(lua, -1) == LUA_TSTRING ? lua_tostring(lua, -1) : NULL;
    fprintf(stderr, "%s\n", message ? message : "Lua script failed.");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s script.lua\n", argv[0]);
    return EXIT_FAILURE;
  }

  ModAlloc allocator = {.cap = MOD_MEM_CAP};
  lua_State *lua = lua_newstate(mod_lua_alloc, &allocator);
  if (!lua) {
    fputs("Could not initialize Lua.\n", stderr);
    return EXIT_FAILURE;
  }

  int result = run_script(lua, argv[1]);
  lua_close(lua);
  return result;
}
