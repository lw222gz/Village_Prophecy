#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawAble.h"
#include "MoveDirection.h"
#include "GameAreas.h"
#include "Path.h"
#include "Inventory.h"

using namespace sf;
using namespace std;

class Player : public IDrawAble
{
public:	
	Player();
	~Player();	
	Areas playerMove(MoveDirection dir, Time *t);
	void setBorders(Vector2u size);
	Vector2f getPosition();
	Vector2u getSize();
	Sprite getSprite();
	void setPlayerPosition(Vector2f pos);
	void setAreaPaths(vector<Path*> areaPaths);

	Inventory* InventoryManager();

private:
	//pixel speed of player per second
	float speed = 300.0;
	//also hold the value for the player size
	Texture playerTexture;
	//Also hold the value for the players position
	Sprite playerSprite;
	Vector2u borders;
	vector<Path*> avaliblePaths;
	Inventory inventoryManager;
};

