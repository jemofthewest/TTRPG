#include <SFML/Graphics.hpp>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "debug.h"
}

#include "TileMap.hpp"

int main()
{
  /* create the window */
  sf::RenderWindow window(sf::VideoMode(640,480), "Tilemap");

  /* Create the viewport */
  sf::View view(sf::Vector2f(500,500), sf::Vector2f(640,480));
  window.setView(view);

  /* open lua state */
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  /* Create map */
  TileMap testMap;
  const char* filename = "testmap.lua";
  testMap.load(L, filename);
  
  /* run the main loop */
  while (window.isOpen())
  {
    /* handle events */
    sf::Event event;
    while (window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::Resized)
      {
        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
        window.setView(sf::View(visibleArea));
      }
    }

    /* draw the map */
    window.clear();
    window.draw(testMap);
    window.display();
  }

  return 0;
}
