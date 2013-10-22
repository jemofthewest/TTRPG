#ifndef TILELAYER_H
#define TILELAYER_H

#include <SFML/Graphics.hpp>

class TileLayer : public sf::Drawable, public sf::Transformable
{
  public:

    void load(lua_State *L, const char* filename, unsigned int layer);

  private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
      // apply the transform
      states.transform *= getTransform();

      // apply the tileset texture
      states.texture = &m_tileset;

      // draw the vertex array
      target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif
