#include <SFML/Graphics.hpp>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "debug.h"
}

#include "TileLayer.hpp"

int main()
{
  // create the window
  sf::RenderWindow window(sf::VideoMode(1024,1024), "Tilemap");

  // open lua state
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  
  TileLayer layer1;
  if (!layer1.load(L, "testmap.lua", 1))
    return -1;

  TileLayer layer2;
  if (!layer2.load(L, "testmap.lua", 2))
    return -1;

  TileLayer layer3;
  if (!layer3.load(L, "testmap.lua", 3))
    return -1;

  TileLayer layer4;
  if (!layer4.load(L, "testmap.lua", 4))
    return -1;

  TileLayer layer5;
  if (!layer5.load(L, "testmap.lua", 5))
    return -1;

  // run the main loop
  while (window.isOpen())
  {
    // handle events
    sf::Event event;
    while (window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
    }

    // draw the map
    window.clear();
    window.draw(layer1);
    window.draw(layer2);
    window.draw(layer3);
    window.draw(layer4);
    window.draw(layer5);
    window.display();
  }

  return 0;
}
