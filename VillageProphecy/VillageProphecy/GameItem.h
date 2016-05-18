#pragma once
#include "ObjectType.h"
#include "IDrawAble.h"
#include "TextureLoader.h"

class GameItem : public IDrawAble
{
public:
	GameItem(GameObjectType itemType, TextureLoader *_textures);
	~GameItem();	
	Sprite getSprite();
	GameObjectType getType();
	int getStackAmount();
	bool isStackAble();
	void addToStack();
	void reduceStackAmount(int amount);

private:
	TextureLoader *textures;
	bool stackAble = false;
	int stackAmount = 1;
	GameObjectType itemType;
	Texture SlotTexture;
	Sprite SlotSprite;
	void setItemSprite();

};

