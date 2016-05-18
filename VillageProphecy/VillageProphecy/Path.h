#pragma once
#include "IDrawAble.h"
#include "GameAreas.h"
#include "Direction.h"
//#include <SFML/Graphics.hpp>

using namespace sf;

class Path : public IDrawAble
{
public:
	Path(Areas area, Direction dir, Vector2f entrance, Texture *pathTexture);
	~Path();
	Vector2f getPosition();
	Sprite getSprite();
	Areas getNextArea();
	Vector2u getSize();
	Direction getDirection();

private:
	Areas leadsTo;
	Vector2f entryPoint;

	Sprite pathSprite;
	Direction direction;
};

