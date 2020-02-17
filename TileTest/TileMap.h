#include <SFML/Graphics/RectangleShape.hpp>

#include <string>
#include <vector>

#include "Tile.h"

class Tile;

class TileMap : public sf::Drawable, public sf::Transformable
{
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	sf::Texture mTileset;


public:

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
	std::vector<Tile> mTiles;
	std::vector<Tile*> mWallTiles;
	//sf::VertexArray* mActiveVertices;
	sf::Vector2u tileSize;
	unsigned int levelWidth;
	unsigned int levelHeight;
	int tileCount;

};