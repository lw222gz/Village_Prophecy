#pragma once
#include "EnemyType.h"
#include "IDrawAble.h"

using namespace std;

class Enemy : public IDrawAble
{
public:
	Enemy(EnemyType typeOfEnemy);
	~Enemy();
	Sprite getSprite();
	EnemyType getEnemyType();
	float getHitPoints();
	float getMaxHitPoints();
	void TakeDamage(float amount);
	bool IsAlive();
	float getAttackDamage();
	void setPosition(float x, float y);

private:
	void setEnemyValues();
	EnemyType type;
	Sprite enemySprite;
	Texture enemyTexture;
	float hitPoints = 100;
	float maxHitPoints = hitPoints;
	float attackDamage = 0;
	int XPGrant = 0;
};

