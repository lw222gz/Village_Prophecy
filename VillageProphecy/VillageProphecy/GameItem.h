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
	int getStackAmount();
	bool isStackAble();
	void addToStack();
	void reduceStackAmount(int amount);

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

