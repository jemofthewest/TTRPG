#include <SFML/Graphics.hpp>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "debug.h"
}

#include "TileLayer.hpp"

void TileLayer::load(lua_State *L, const char* filename, unsigned int layer)
{
  unsigned int mapwidth, mapheight, tilewidth, tileheight;
  unsigned int numTilesets, dataSize;
  sf::Vector2u tileSize;
  std::string tileset;

  /* Load script */
  luaL_dofile(L, filename);
  if (!lua_istable(L, -1))
    error(L, "Loading script went wrong");

  /* load the tileset texture */
  lua_getfield(L, -1, "tilesets");
  lua_len(L, -1);
  numTilesets = lua_tointeger(L, -1);
  lua_pop(L, 1);
  if (!numTilesets == 1)
    error(L, "Too many tilesets");
  lua_rawgeti(L, -1, 1);
  lua_getfield(L, -1, "image");
  tileset = lua_tolstring(L, -1, NULL);
  lua_pop(L, 3);
  if (!m_tileset.loadFromFile(tileset))
    error(L, "Loading tileset went wrong");

  /* Get width and height of map */
  lua_getfield(L, -1, "width");
  mapwidth = lua_tointeger(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, -1, "height");
  mapheight = lua_tointeger(L, -1);
  lua_pop(L, 1);

  /* Assume each layer is width x height */
  dataSize = mapwidth*mapheight;

  /* Get tile width and height */
  lua_getfield(L, -1, "tilewidth");
  tilewidth = lua_tointeger(L, -1);
  lua_pop(L, 1);

  lua_getfield(L, -1, "tileheight");
  tileheight = lua_tointeger(L, -1);
  lua_pop(L, 1);
  
  tileSize = sf::Vector2u(tilewidth, tileheight);

  /* Get tile map */
  lua_getfield(L, -1, "layers");
  int tiles[dataSize];
  lua_rawgeti(L, -1, layer);

  lua_getfield(L, -1, "data");
  for (unsigned int j = 1; j <= dataSize; j++)
  {
    lua_rawgeti(L, -1, j);
    tiles[j-1] = lua_tointeger(L, -1) - 1;
    lua_pop(L, 1); // local value
  } 

  lua_pop(L, 2); // table and data
  lua_pop(L, 1); // layers

  /* resize the vertex array to fit the level size */
  m_vertices.setPrimitiveType(sf::Quads);
  m_vertices.resize(mapwidth * mapheight * 4);

  /* populate the vertex array, with one quad per tile */
  for (unsigned int i = 0; i < mapwidth; ++i)
  {
    for (unsigned int j = 0; j < mapheight; ++j)
    {
      // get the current tile number
      int tileNumber = tiles[i + j * mapwidth];

      // find its position in the tileset texture
      int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
      int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

      // get a pointer to the current tile's quad
      sf::Vertex* quad = &m_vertices[(i + j * mapwidth) * 4];

      // define its 4 corners
      quad[0].position = sf::Vector2f(i * tileSize.x, j*tileSize.y);
      quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
      quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
      quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

      // define its 4 texture coordinates
      quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
      quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
      quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
      quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }
  }
}
