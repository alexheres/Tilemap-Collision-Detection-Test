#ifndef _QUADTREE_H
#define _QUADTREE_H

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

using std::vector;

class Tile;

class Quadtree 
{

	enum Node {
		NW = 0,
		NE,
		SW,
		SE,
		NodeCount
	};

public:
	Quadtree();
	Quadtree(float _x, float _y, float _width, float _height, unsigned int _level, unsigned int growNum = 4);
	~Quadtree();

	void					AddObject(Tile *object);
	vector<Tile*>			GetObjectsAt(const sf::FloatRect &rect);
	void					Clear();

	bool					contains(Tile *object);
	bool					contains(const sf::FloatRect &rect);

	void					SetFont(const sf::Font &font);
	void					Draw(sf::RenderTarget &canvas);

private:
	float					x;
	float					y;
	float					width;
	float					height;
	unsigned int			level;
	unsigned int			maxLevel;
	unsigned int			numObjectsToGrow;

	vector<Tile*>			objects;

	Quadtree *				nodes;

	sf::RectangleShape		shape;
	sf::Text				text;

	bool				isLeaf;

	void				createLeaves();
	void				moveObjectsToLeaves();
};

#endif