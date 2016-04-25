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

private:
	void setEnemyTexture();
	EnemyType type;
	Sprite enemySprite;
	Texture enemyTexture;
	float hitPoints = 100;
	float maxHitPoints = hitPoints;
	bool isAlive = true;
};

