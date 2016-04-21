#include "Enemy.h"


Enemy::Enemy(EnemyType typeOfEnemy, Vector2f pos) : type(typeOfEnemy)
{
	enemySprite.setPosition(pos);
}


Enemy::~Enemy()
{
}

Sprite Enemy::getSprite(){
	return enemySprite;
}


void Enemy::setEnemyTexture(){
	switch (type)
	{
	case Skeleton_MELEE:
		if (!enemyTexture.loadFromFile("Textures/PHEnemy.png")){
			throw "TEXTURE LOAD ERROR: Enemy::Skeleton could not load texture.";
		}
		
		break;

	case Human_MELEE:
		//TODO: add own texture
		if (!enemyTexture.loadFromFile("Textures/PHEnemy.png")){
			throw "TEXTURE LOAD ERROR: Enemy::Skeleton could not load texture.";
		}
		break;

	default:
		throw "SET TEXTURE ERROR: Not a valid enemy type was given.";
		break;
	}

	enemySprite.setTexture(enemyTexture);
}