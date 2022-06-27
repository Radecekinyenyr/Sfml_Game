#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/VertexArray.hpp>
#include "Collision.h"

int blockCount = 0;
class TileMap : public sf::Drawable, public sf::Transformable
{

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture

        // draw the vertex array
        target.draw(m_vertices);
    }

    std::vector<BlockPosition> blockPosition;

    sf::VertexArray m_vertices;

public:

    void load(sf::Vector2u tileSize, unsigned int width, unsigned int height, char tilemap[12][25])
    {
      
        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number

                // find its position in the tileset texture
               
                // get a pointer to the current tile's quad
               
                if (tilemap[j][i] == '#') {
                    sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
                    // define its 4 corners
                    quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                    quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                    quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                    quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                    quad->color = sf::Color::White;
                    
                    blockPosition.push_back(BlockPosition());
                    blockPosition[blockCount].topLeft = quad[0].position;
                    blockPosition[blockCount].topRight = quad[1].position;
                    blockPosition[blockCount].bottomRight = quad[2].position;
                    blockPosition[blockCount].bottomLeft = quad[3].position;

                    ++blockCount;
                }
                
            }
     
    }

    std::vector<BlockPosition> getBlockPosition()
    {
        return blockPosition;
    }

};