#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#ifndef TILE_H
#define TILE_H

class Tile : public sf::Drawable, public sf::Transformable
{

public:


	Tile(const int &tileNum, const sf::Vector2f &NWpos, const sf::Vector2f &NWtex,
							 const sf::Vector2f &NEpos, const sf::Vector2f &NEtex,
							 const sf::Vector2f &SEpos, const sf::Vector2f &SEtex,
							 const sf::Vector2f &SWpos, const sf::Vector2f &SWtex,
		 const bool &wall);
	
	~Tile();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void activate();
	void deactivate();

	sf::Vertex mVertices[4];
	sf::ConvexShape mHitbox;
	int tileNumber;
	bool isActive;
	bool isWall;

};

#endif // TILE_H
