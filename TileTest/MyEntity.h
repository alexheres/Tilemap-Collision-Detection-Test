#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


class MyEntity : public sf::Drawable, public sf::Transformable
{
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	sf::VertexArray		mVertices;
	sf::Texture			mTexture;

};

