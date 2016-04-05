#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//Everything in a struct is public
class IDrawAble{
public:
	virtual Vector2f getPosition() = 0;
	virtual Sprite getSprite() = 0;

};