#include "TileMap.h"
#include <iostream>
#include <string>

bool TileMap::load(const std::string& tileset, sf::Vector2u tSize, const int* tiles, unsigned int width, unsigned int height)
{
	// load the tileset texture
	if (!mTileset.loadFromFile(tileset))
		return false;

	//mActiveVertices = new sf::VertexArray();
	//mActiveVertices->setPrimitiveType(sf::Quads);

	tileSize = tSize;
	levelWidth = width;
	levelHeight = height;

	/*
	/	Populate the vertex vector, with one quad per tile.
	/	Tiles are loaded in column-major fashion, filling each column from top-to-bottom.
	/	Only creates 'useful' tiles, and not 'useless' tiles, to optimize space and time.
	/	(i.e. "transparent" tiles that are for the background.)
	*/
	tileCount = 0;
	for (unsigned int i = 0; i < levelWidth; ++i)
		for (unsigned int j = 0; j < levelHeight; ++j)
		{
			bool stat = false;
			//std::cout << "i = " << i << ", j = " << j << std::endl;

			// get the current tile number
			int tileNumber = tiles[i + j * levelWidth];

			//std::cout << "mapNums[i+j] = " << mapNums[i+j] << std::endl;

			if (tileNumber != -1)
			{
				// determine staticness
				// if tile is not on the border and is touching a "-1" tile, it is collidable
				if ((i != 0 && i != (levelWidth - 1) && j != 0 && j != (levelHeight - 1) &&
					(tiles[(i + j * levelWidth) - 1] == -1 ||
						tiles[(i + j * levelWidth) + 1] == -1 ||
						tiles[(i + (j - 1) * levelWidth)] == -1 ||
						tiles[(i + (j + 1) * levelWidth)] == -1)))
					stat = true;

				// find its corresponding position in the tileset texture
				int tu = tileNumber % (mTileset.getSize().x / tileSize.x);
				int tv = tileNumber / (mTileset.getSize().x / tileSize.x);

				// add the current tile's quad to the vertex vector, 
				// recording each of it's corners for both its world position and its texture coordinates
				// NW corner
				mTiles.push_back(Tile(tileNumber, sf::Vector2f(i * tileSize.x, j * tileSize.y),
												  sf::Vector2f(tu * tileSize.x, tv * tileSize.y),
												  sf::Vector2f((i + 1.f) * tileSize.x, j * tileSize.y),
												  sf::Vector2f((tu + 1.f) * tileSize.x, tv * tileSize.y),
												  sf::Vector2f((i + 1.f) * tileSize.x, (j + 1.f) * tileSize.y),
												  sf::Vector2f((tu + 1.f) * tileSize.x, (tv + 1.f) * tileSize.y),
												  sf::Vector2f(i * tileSize.x, (j + 1.f) * tileSize.y),
												  sf::Vector2f(tu * tileSize.x, (tv + 1.f) * tileSize.y),
									  stat));

				tileCount++;


			}
		}

	for (int i = 0; i < mTiles.size(); i++)
	{
		if (mTiles[i].isWall)
		{
			mWallTiles.push_back(&mTiles[i]);
		}
	}

	return true;
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();
	// apply the tileset texture
	states.texture = &mTileset;

	// get the current view's rectangle
	sf::FloatRect screenRect(sf::Vector2f(target.getView().getCenter().x - (target.getView().getSize().x) / 2, target.getView().getCenter().y - (target.getView().getSize().y) / 2), target.getView().getSize());
	int tilesDrawn = 0;

	// draw the tiles
	for (int i = 0; i < mTiles.size(); i++)
	{
		if (screenRect.intersects(sf::FloatRect(mTiles[i].mVertices[0].position.x, mTiles[i].mVertices[0].position.y, tileSize.x, tileSize.y)))
		{
			if (mTiles[i].isActive)
			{
				//mActiveVertices->append(mTiles[i].mVertices[0]);
				//mActiveVertices->append(mTiles[i].mVertices[1]);
				//mActiveVertices->append(mTiles[i].mVertices[2]);
				//mActiveVertices->append(mTiles[i].mVertices[3]);
				
				target.draw(mTiles[i], states);
				// target.draw(mTiles[i].mHitbox, states);
				tilesDrawn++;

			}
		}
		//target.draw(*mActiveVertices, states);
		//mActiveVertices->clear();
		
	}

	std::cout << "Tiles Drawn: " << tilesDrawn << std::endl;

}
