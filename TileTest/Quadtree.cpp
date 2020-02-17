#include "Quadtree.h"
#include "Tile.h"
#include <iostream>
#include <sstream>


Quadtree::Quadtree() :
	x(0),
	y(0),
	width(0),
	height(0),
	level(0),
	maxLevel(4),
	numObjectsToGrow(4),
	nodes(0),
	isLeaf(true)
{
}

Quadtree::Quadtree(float _x, float _y, float _width, float _height, unsigned int _level, unsigned int growNum) :
	x(_x),
	y(_y),
	width(_width),
	height(_height),
	numObjectsToGrow(growNum),
	level(_level),
	maxLevel(4),
	nodes(0),
	isLeaf(true)
{
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(width, height));
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineThickness(1.0f);
	shape.setOutlineColor(sf::Color(64, 128, 255));
	/*text.setPosition(x, y + level * 16);
	text.setCharacterSize(12);*/

}

Quadtree::~Quadtree()
{
	if (!isLeaf)
		delete[] nodes;
}

// Adds an entity to the Quadtree, based on 
// the position of its hitbox (or Sprite bounds)
void Quadtree::AddObject(Tile *object)
{
	if (isLeaf)
	{
		//std::cout << "objectSize = " << objects.size() << std::endl;
		objects.push_back(object);
		bool reachedMaxObjects = (objects.size() == numObjectsToGrow);
		if (reachedMaxObjects && level < maxLevel)
		{
			createLeaves();
			moveObjectsToLeaves();
			isLeaf = false;
		}

		return;
	}

	for (int n = 0; n < NodeCount; ++n)
	{
		if (nodes[n].contains(object))
		{
			nodes[n].AddObject(object);
			return;
		}
	}

	objects.push_back(object);
}

/*
/ Returns a vector of all the objects to be checked for collision,
/ based on given rectangle. AABB testing is used for collision.
*/
vector<Tile*> Quadtree::GetObjectsAt(const sf::FloatRect &rect)
{

	if (isLeaf)
	{
		return objects;
	}

	vector<Tile*> returnedObjects;
	vector<Tile*> childObjects;

	if (!objects.empty())
		returnedObjects.insert(returnedObjects.end(), objects.begin(), objects.end());

	for (int n = 0; n < NodeCount; ++n)
	{
		if (nodes[n].contains(rect))
		{
			childObjects = nodes[n].GetObjectsAt(rect);
			returnedObjects.insert(returnedObjects.end(), childObjects.begin(), childObjects.end());
			//break;
		}
	}

	return returnedObjects;
}

// clear all the nodes of the Quadtree recursively
void Quadtree::Clear()
{
	objects.clear();

	if (!isLeaf)
	{
		for (int n = 0; n < NodeCount; ++n)
		{
			nodes[n].Clear();
		}
	}
}

// set the font for display
void Quadtree::SetFont(const sf::Font &font)
{
	/*text.setFont(font);
	if (level != maxLevel)
	{
	NW->SetFont(font);
	NE->SetFont(font);
	SW->SetFont(font);
	SE->SetFont(font);
	}*/
}

// draws Quadtree partitions onto the screen
void Quadtree::Draw(sf::RenderTarget &canvas)
{
	//stringstream ss;
	//ss << objects.size();
	//string numObjectsStr = ss.str();
	//text.setString(numObjectsStr);
	//canvas.draw(text);
	canvas.draw(shape);
	if (!isLeaf)
	{
		for (int n = 0; n < NodeCount; ++n)
		{
			nodes[n].Draw(canvas);
		}
	}
}

bool Quadtree::contains(Tile* object)
{
	/*std::cout << "(objects)\nobject->x = " << object->x << " should be greater than this->x = " << x <<
	"\nobject->y = " << object->y << " should be greater than this->y = " << y <<
	"\nobject->width + object->x = " << object->width + object->x << " should be less than this->width + this->x = " << width + x<<
	"\nobject->height + object->y = " << object->height + object->y << " should be less than this->height + this->y = " << height + y << std::endl;

	std::cout << (object->x > x &&
	object->width + object->x < x + width &&
	object->y > y &&
	object->height + object->y < y + height) << std::endl;*/

	return 	object->mVertices[0].position.x > x &&
			(object->mVertices[1].position.x - object->mVertices[0].position.x) + object->mVertices[0].position.x < x + width &&
			object->mVertices[0].position.y > y &&
			(object->mVertices[3].position.y - object->mVertices[0].position.y) + object->mVertices[0].position.y < y + height;
}

bool Quadtree::contains(const sf::FloatRect &rect)
{
	/*std::cout << "(floats)\nInputX = " << _x << " should be greaterOrEqual to this->x = " << x <<
	"\nInputX = " << _x << " should be lessOrEqual to this->width + this->x = " << x + width <<
	"\nInputY = " << _y << " should be greaterOrEqual to this->y = " << y <<
	"\nInputY = " << _y << " should be lessOrEqual to this->height + this->y = " << y + height << std::endl;

	std::cout << ((_x >= x && _x <= x + width) &&
	(_y >= y && _y <= y + height)) << std::endl;*/
	//std::cout << "rect.left = " << rect.left << ", rect.top = " << rect.top
	//		<< ", rect.width = " << rect.width << ", rect.height = " << rect.height << std::endl;

	//	std::cout << "this.x = " << x << ", this.y = " << y
	//<< ", this.width = " << width << ", this.height = " << height << std::endl;

	if (rect.left > x + width || x > rect.left + rect.width ||
		rect.top > y + height || y > rect.top + rect.height) {
		return false;
	}

	else
		return true;
}

void Quadtree::createLeaves()
{
	nodes = new Quadtree[4];
	nodes[NW] = Quadtree(x, y, width / 2.0f, height / 2.0f, level + 1, numObjectsToGrow);
	nodes[NE] = Quadtree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level + 1, numObjectsToGrow);
	nodes[SW] = Quadtree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level + 1, numObjectsToGrow);
	nodes[SE] = Quadtree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level + 1, numObjectsToGrow);
	//std::cout << "x = " << x << ", y = " << y << ", width = " << width << ", height = " << height << std::endl;
}

void Quadtree::moveObjectsToLeaves()
{
	for (int n = 0; n < NodeCount; ++n)
	{
		for (unsigned int m = 0; m < objects.size(); ++m)
		{
			if (nodes[n].contains(objects[m]))
			{
				nodes[n].AddObject(objects[m]);
				objects.erase(objects.begin() + m);
				--m;
			}
		}
	}
}

