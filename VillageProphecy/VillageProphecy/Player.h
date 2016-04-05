#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawAble.h"
#include "MoveDirection.h"
#include "GameAreas.h"
#include "Path.h"

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
	Sprite getSprite();
	void setPlayerPosition(Vector2f pos);
	void setAreaPaths(vector<Path*> areaPaths);
	

private:
	//speed of player
	float speed = 300.0;
	//also hold the value for the player size
	Texture playerTexture;
	//Also hold the value for the players position
	Sprite playerSprite;
	Vector2u borders;
	vector<Path*> avaliblePaths;
};

