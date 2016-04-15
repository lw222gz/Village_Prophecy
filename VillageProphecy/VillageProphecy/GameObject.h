#pragma once
//#include "ObjectType.h"
//#include "IDrawAble.h"
#include "Player.h"
#include "TriggerType.h"
//#include "MaterialList.h"
//#include <SFML/Graphics.hpp>


using namespace sf;

//http://stackoverflow.com/questions/6515143/user-created-header-causing-c2061-syntax-error-identifier-classname
class Player; //Forward decleration
class MaterialList; //Forward decleration

class GameObject : public IDrawAble
{
public:
	GameObject(GameObjectType objectType, Vector2f pos);
	~GameObject();
	Sprite getSprite();
	bool isTriggerd(Player *p);
	TriggerType getTriggerType();
	GameObjectType getObjectType();

	MaterialList* MaterialListManager();
	void completeConstruction();

private:
	TriggerType triggerType = TriggerType::No_Action;
	float triggerRange = 50;
	GameObjectType type;
	Sprite objectSprite;
	//TODO: -optimization- have a static texture loaded for each possible texture
	Texture objectTexture;
	void setObjectSprite();

	//buildable objects that are not constructed yet
	//should have a 50% opacity
	float opacity = 1;
	//List of materials to construct object.
	//ONLY USED FOR BUILDABLE GAME OBJECTS
	MaterialList *materialList = NULL;
	
};

