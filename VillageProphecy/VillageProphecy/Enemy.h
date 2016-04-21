#pragma once
#include "EnemyType.h"
#include "IDrawAble.h"

using namespace std;

class Enemy : public IDrawAble
{
public:
	Enemy(EnemyType typeOfEnemy, Vector2f pos);
	~Enemy();
	Sprite getSprite();

private:
	void setEnemyTexture();
	EnemyType type;
	Sprite enemySprite;
	Texture enemyTexture;
};

