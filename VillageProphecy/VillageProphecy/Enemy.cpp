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

float Enemy::getHitPoints(){
	return hitPoints;
}

float Enemy::getMaxHitPoints(){
	return maxHitPoints;
}

void Enemy::TakeDamage(float amount){
	hitPoints -= amount;
	isAlive = hitPoints > 0;
}

bool Enemy::IsAlive(){
	return isAlive;
}


void Enemy::setEnemyTexture(){
	switch (type)
	{
		case Skeleton_MELEE:
			if (!enemyTexture.loadFromFile("Textures/PHEnemy.png")){
				throw "TEXTURE LOAD ERROR: Enemy::Skeleton could not load texture.";
			}
			hitPoints = 20;
			break;

		case Human_MELEE:
			//TODO: add own texture
			if (!enemyTexture.loadFromFile("Textures/PHEnemy.png")){
				throw "TEXTURE LOAD ERROR: Enemy::Skeleton could not load texture.";
			}
			break;
			hitPoints = 50;
		default:
			throw "SET TEXTURE ERROR: Not a valid enemy type was given.";
			break;
	}

	maxHitPoints = hitPoints;
	enemySprite.setTexture(enemyTexture);
}