#pragma once
#include "ObjectType.h"
#include "IDrawAble.h"

class GameItem : public IDrawAble
{
public:
	GameItem(GameObjectType itemType);
	~GameItem();	
	Sprite getSprite();
	GameObjectType getType();
	void setSlotPosition(Vector2f);
	int getStackAmount();
	bool isStackAble();
	void addToStack();

private:
	bool stackAble = false;
	int stackAmount = 1;
	GameObjectType itemType;
	Sprite itemSprite;
	//TODO: check the problem that occured when the texture is static
	//It crashed the game
	Texture emptySlotTexture;
	Texture woodSlotTexture;
	void setItemSprite();

};

