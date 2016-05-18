#pragma once
#include "Enemy.h"
#include "TextureLoader.h"

//<Summary>
//A visual enemy is one enemy the player can collide into, when combat then starts
//this can be a group of enemies.

class VisualEnemy : public IDrawAble
{
public:
	VisualEnemy(EnemyVisualType visualType, Vector2f pos, int level, TextureLoader *_textures);
	~VisualEnemy();
	Sprite getSprite();
	bool collideWithPlayer(Vector2f playerPos, Vector2u playerSize);
	vector<Enemy*>* getEnemyGroup();

	int getEnemyLevel();
	EnemyVisualType getType();

private:
	TextureLoader *textures;

	Sprite enemySprite;
	Texture enemyTexture;
	EnemyVisualType type;
	vector<Enemy*> enemyGroup;
	int enemyGroupLevel = 0;

	void setValues();
	void generareMobGroup();
	int amountOfMobs;
};

