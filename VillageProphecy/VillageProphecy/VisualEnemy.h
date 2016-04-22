#pragma once
#include "Enemy.h"

//<Summary>
//A visual enemy is one enemy the player can collide into, when combat then starts
//this can be a group of enemies.

class VisualEnemy : public IDrawAble
{
public:
	VisualEnemy(EnemyVisualType visualType, Vector2f pos);
	~VisualEnemy();
	Sprite getSprite();
	bool collideWithPlayer(Vector2f playerPos, Vector2u playerSize);
	vector<Enemy*>* getEnemyGroup();

private:
	Sprite enemySprite;
	Texture enemyTexture;
	EnemyVisualType type;
	vector<Enemy*> enemyGroup;

	void setValues();
	void generareMobGroup();
	int amountOfMobs;
};

