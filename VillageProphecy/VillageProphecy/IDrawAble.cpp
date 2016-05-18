#include "IDrawAble.h"

/*
* <DESCRIPTION>
* Reflects a sprite to face the oposite direction
*
* @PARAMS
* sprite: pointer to a Sprite object that is having it's facing direction switched.
*/
void IDrawAble::ReflectSprite(Sprite *sprite){

	sprite->setOrigin(sprite->getLocalBounds().width, 0);
	sprite->setScale(-1.f, 1.f);
}

/*
* <DESCRIPTION>
* Resets a reflection of a sprite and makes it face it's defualt way.
*
* @PARAMS
* sprite: pointer to a Sprite object that is having it's facing direction reset.
*/
void IDrawAble::ResetReflectSprite(Sprite *sprite){

	sprite->setOrigin(0, 0);
	sprite->setScale(1.f, 1.f);
}