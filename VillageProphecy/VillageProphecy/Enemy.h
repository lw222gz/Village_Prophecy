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
	int getHitPoints();
	int getMaxHitPoints();
	void TakeDamage(int amount);
	bool IsAlive();
	int getAttackDamage();
	void setPosition(int x, int y);
	int getXPGrant();
	
	vector<EnemySkill*> *getEnemySkills();

private:
	void setEnemyStats();
	void setEnemySkills();
	EnemyType type;
	Sprite enemySprite;
	Texture enemyTexture;
	int hitPoints = 100;
	int maxHitPoints = hitPoints;
	int attackDamage = 0;
	int XPGrant = 0;
	int level = 0;

	vector<EnemySkill*> enemySkills;

	void LevelBonus();
	const double levelBonus = .25;
};

