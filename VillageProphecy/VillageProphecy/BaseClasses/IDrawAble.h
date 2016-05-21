#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//TODO: Merge this "interface" with a gameObject interface?
class IDrawAble{
public:
	virtual Sprite getSprite() = 0;
	void ReflectSprite(Sprite *sprite);
	void ResetReflectSprite(Sprite *sprite);
};