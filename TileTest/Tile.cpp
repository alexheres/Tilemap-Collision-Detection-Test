#include "Tile.h"

Tile::Tile(const int &tileNum, const sf::Vector2f &NWpos, const sf::Vector2f &NWtex,
							   const sf::Vector2f &NEpos, const sf::Vector2f &NEtex,
							   const sf::Vector2f &SEpos, const sf::Vector2f &SEtex,
							   const sf::Vector2f &SWpos, const sf::Vector2f &SWtex,
		   const bool &wall)
	: isActive(true)
	, isWall(wall)
{
	tileNumber = tileNum;

	mVertices[0] = sf::Vertex(NWpos, NWtex);
	mVertices[1] = sf::Vertex(NEpos, NEtex);
	mVertices[2] = sf::Vertex(SEpos, SEtex);
	mVertices[3] = sf::Vertex(SWpos, SWtex);

	// left 45-degree slope
	if (tileNumber == 1)
	{
		mHitbox.setPointCount(4);
		mHitbox.setPosition(sf::Vector2f(mVertices[0].position.x, mVertices[0].position.y));
		mHitbox.setPoint(0, sf::Vector2f(0.f, 0.f));
		mHitbox.setPoint(1, sf::Vector2f(0.f, 0.f));
		mHitbox.setPoint(2, sf::Vector2f(32.f, 32.f));
		mHitbox.setPoint(3, sf::Vector2f(0.f, 32.f));
		mHitbox.setFillColor(sf::Color::Transparent);
		mHitbox.setOutlineColor(sf::Color::Green);
		mHitbox.setOutlineThickness(1.5f);
	}
	// right 45-degree slope
	else if (tileNumber == 2)
	{
		mHitbox.setPointCount(3);
		mHitbox.setPosition(sf::Vector2f(mVertices[0].position.x, mVertices[0].position.y));
		mHitbox.setPoint(0, sf::Vector2f(0.f, 32.f));
		mHitbox.setPoint(1, sf::Vector2f(32.f, 0.f));
		mHitbox.setPoint(2, sf::Vector2f(32.f, 32.f));
		mHitbox.setFillColor(sf::Color::Transparent);
		mHitbox.setOutlineColor(sf::Color::Green);
		mHitbox.setOutlineThickness(1.5f);
	}
	// right ramp, lower
	else if (tileNumber == 5)
	{
		mHitbox.setPointCount(4);
		mHitbox.setPosition(sf::Vector2f(mVertices[0].position.x, mVertices[0].position.y));
		mHitbox.setPoint(0, sf::Vector2f(0.f, 32.f));
		mHitbox.setPoint(1, sf::Vector2f(32.f, 16.f));
		mHitbox.setPoint(2, sf::Vector2f(32.f, 32.f));
		mHitbox.setPoint(3, sf::Vector2f(0.f, 32.f));
		mHitbox.setFillColor(sf::Color::Transparent);
		mHitbox.setOutlineColor(sf::Color::Green);
		mHitbox.setOutlineThickness(1.5f);
	}
	// right ramp, upper
	else if (tileNumber == 6)
	{
		mHitbox.setPointCount(4);
		mHitbox.setPosition(sf::Vector2f(mVertices[0].position.x, mVertices[0].position.y));
		mHitbox.setPoint(0, sf::Vector2f(0.f, 16.f));
		mHitbox.setPoint(1, sf::Vector2f(32.f, 0.f));
		mHitbox.setPoint(2, sf::Vector2f(32.f, 32.f));
		mHitbox.setPoint(3, sf::Vector2f(0.f, 32.f));
		mHitbox.setFillColor(sf::Color::Transparent);
		mHitbox.setOutlineColor(sf::Color::Green);
		mHitbox.setOutlineThickness(1.5f);
	}
	// default square
	else
	{
		mHitbox.setPointCount(4);
		mHitbox.setPosition(sf::Vector2f(mVertices[0].position.x, mVertices[0].position.y));
		mHitbox.setPoint(0, sf::Vector2f(0.f, 0.f));
		mHitbox.setPoint(1, sf::Vector2f(32.f, 0.f));
		mHitbox.setPoint(2, sf::Vector2f(32.f, 32.f));
		mHitbox.setPoint(3, sf::Vector2f(0.f, 32.f));
		mHitbox.setFillColor(sf::Color::Transparent);
		mHitbox.setOutlineColor(sf::Color::Green);
		mHitbox.setOutlineThickness(1.5f);
	}

	
}

Tile::~Tile()
{

}



void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mVertices, 4, sf::Quads, states);
	//target.draw(mHitbox, states);


}

void Tile::activate()
{
	isActive = true;
}

void Tile::deactivate()
{
	isActive = false;
}
