#pragma once
#include "EnemyType.h"
#include "IDrawAble.h"


class EnemySkill;

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
	vector<EnemySkill*> *getEnemySkills();


private:
	void setEnemyStats();
	void setEnemySkills();
	EnemyType type;
	Sprite enemySprite;
	Texture enemyTexture;
	float hitPoints = 100;
	float maxHitPoints = hitPoints;
	float attackDamage = 0;
	int XPGrant = 0;
	int level = 0;

	vector<EnemySkill*> enemySkills;

	void LevelBonus();
	const float levelBonus = .25;
};

