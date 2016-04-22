#include "Enemy.h"


Enemy::Enemy(EnemyType typeOfEnemy) : type(typeOfEnemy)
{
	setEnemyTexture();
}


Enemy::~Enemy()
{
}

Sprite Enemy::getSprite(){
	return enemySprite;
}

EnemyType Enemy::getEnemyType(){
	return type;
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