extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "debug.h"
}

#include "TileMap.hpp"

void TileMap::load(lua_State *L, const char* filename)
{
  unsigned int i;

  luaL_dofile(L, filename);
  if (!lua_istable(L, -1))
    error(L, "Loading script went wrong");

  lua_getfield(L, -1, "layers"); 
  lua_len(L, -1);
  numLayers = lua_tointeger(L, -1);
  lua_pop(L, 3); // len, layers, map table

  mapLayers = new TileLayer [numLayers];

  for (i = 0; i < numLayers; i++)
  {
    mapLayers[i].load(L, filename, i+1);
  }
}
