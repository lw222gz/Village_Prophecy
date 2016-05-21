#include "IGameObject.h"

/*
* <DESCRIPTION>
* Checks if the game object is trigger ready by the player.
*
* @PARAMS
* p: pointer to the Player object to check collision
*
* @RETURNS
* returns boolean, true if the player is close enough to trigger the game object.
*/
bool IGameObject::isTriggerd(Player *p){	
	if (p->getPosition().x + p->getSize().x >= objectSprite.getPosition().x - triggerRange &&
		p->getPosition().x <= objectSprite.getPosition().x + objectSprite.getTexture()->getSize().x + triggerRange &&
		p->getPosition().y + p->getSize().y >= objectSprite.getPosition().y - triggerRange &&
		p->getPosition().y <= objectSprite.getPosition().y + objectSprite.getTexture()->getSize().y + triggerRange)
	{		
		return true;
	}
	else{
		return false;
	}
}