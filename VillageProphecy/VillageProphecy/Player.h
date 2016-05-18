#pragma once
//#include <SFML/Graphics.hpp>
#include "Inventory.h"
//#include "IDrawAble.h"
#include "MoveDirection.h"
//#include "GameAreas.h"
#include "Path.h"
#include "PlayerStatsManager.h"


using namespace sf;
using namespace std;

//http://stackoverflow.com/questions/6515143/user-created-header-causing-c2061-syntax-error-identifier-classname
class Inventory; //forward decleration

class Player : public IDrawAble
{
public:	
	Player(TextureLoader *_textures);
	~Player();	
	Areas playerMove(MoveDirection dir, Time *t);
	void setBorders(Vector2u size);
	Vector2f getPosition();
	Vector2u getSize();
	Sprite getSprite();
	void setPlayerPosition(Vector2f pos);
	void setAreaPaths(vector<Path*> areaPaths);	

	void Sleep(bool hasBurningFirePlace);
	void savePosition();
	void setToSavedPosition();

	void ReflectPlayerSprite();
	void ResetPlayerReflectSprite();

	Inventory *InventoryManager();
	PlayerSkillManager *SkillManager();
	PlayerStatsManager *StatsManager();

private:
	TextureLoader *textures;
	//pixel speed of player per second
	float speed = 300.0;

	//Also hold the value for the players position
	Sprite playerSprite;
	Vector2f playerCombatPosition = Vector2f(500.0,500.0);
	Vector2u borders;
	vector<Path*> avaliblePaths;
	
	Vector2f savedPosition = Vector2f(0, 0);
	
	Inventory *inventory = NULL;
	PlayerSkillManager skillManager;
	PlayerStatsManager statsManager = PlayerStatsManager(&skillManager);
};

