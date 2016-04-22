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

private:
	void setEnemyTexture();
	EnemyType type;
	Sprite enemySprite;
	Texture enemyTexture;
};

