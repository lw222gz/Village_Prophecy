#pragma once
#include "EnemyType.h"
#include "IDrawAble.h"

using namespace std;

class Enemy : public IDrawAble
{
public:
	Enemy(EnemyType typeOfEnemy, int level);
	~Enemy();
	Sprite getSprite();
	EnemyType getEnemyType();
	float getHitPoints();
	float getMaxHitPoints();
	void TakeDamage(float amount);
	bool IsAlive();
	float getAttackDamage();
	void setPosition(float x, float y);
	int getXPGrant();

private:
	void setEnemyValues();
	EnemyType type;
	Sprite enemySprite;
	Texture enemyTexture;
	float hitPoints = 100;
	float maxHitPoints = hitPoints;
	float attackDamage = 0;
	int XPGrant = 0;
	int level = 0;

	void LevelBonus();
	const float levelBonus = .25;
};

