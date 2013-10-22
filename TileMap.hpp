#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include "TileLayer.hpp"

class TileMap : public sf::Drawable
{
  public:

    void load(lua_State *L, const char* filename);

  private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
      unsigned int i;

      for (i = 0; i < numLayers; i++)
        target.draw(mapLayers[i],states);
    }

    TileLayer* mapLayers;
    unsigned int numLayers;
};

#endif
