#pragma once
//#include <SFML/Graphics.hpp>
#include "Inventory.h"
//#include "IDrawAble.h"
#include "MoveDirection.h"
//#include "GameAreas.h"
#include "Path.h"


using namespace sf;
using namespace std;

//http://stackoverflow.com/questions/6515143/user-created-header-causing-c2061-syntax-error-identifier-classname
class Inventory; //forward decleration

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
	void Sleep();
	void savePosition();
	void setToSavedPosition();

	int getRemaningActionPoints();
	int getMaxActionsPoints();
	void ConsumeActionPoints(int amount);
	Sprite getAPSprite();
	Sprite getConsumedAPSprite();

	float getPlayerHP();
	float getMaxPlayerHP();
	void damagePlayer(int amount);

	float getPlayerHunger();
	float getPlayerMood();
	float getPlayerStamina();

	float getPlayerMAXHunger();
	float getPlayerMAXMood();
	float getPlayerMAXStamina();

	void playerHungerAffected(float amount);
	void playerMoodAffected(float amount);
	void playerStaminaAffected(float amount);

private:
	//pixel speed of player per second
	float speed = 300.0;
	//also hold the value for the player size
	Texture playerTexture;
	//Also hold the value for the players position
	Sprite playerSprite;
	Vector2f playerCombatPosition = Vector2f(500.0,500.0);
	Vector2u borders;
	vector<Path*> avaliblePaths;
	Inventory *inventory = NULL;
	Vector2f savedPosition = Vector2f(0, 0);

	const int ACTION_POINTS_MAX = 10;
	int actionPoints = 2;
	Texture APTexture;
	Texture consumedAPTexture;
	Sprite APSprite;
	Sprite consumedAPSprite;


	const float BASE_HIT_POINTS = 100;
	float playerHitpoints = BASE_HIT_POINTS;

	const float MAX_HUNGER_POINTS = 100;
	const float MAX_MOOD_POINTS = 100;
	const float MAX_STAMINA_POINTS = 100;

	float currentHunger = MAX_HUNGER_POINTS;
	float currentMood = MAX_MOOD_POINTS;
	float currentStamina = MAX_STAMINA_POINTS;
};

