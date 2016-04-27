#include "Enemy.h"

/*
* <DESCRIPTION>
* Constructor for the Enemy class 
* Calls the setEnemyValues method to set the values for the object.
*
* @PARAMS
* typeOfEnemy: EnemyType enum value that describes the enemy rewards, stats and how it will act
*/
Enemy::Enemy(EnemyType typeOfEnemy) : type(typeOfEnemy)
{
	setEnemyValues();
}


Enemy::~Enemy()
{
}


/*
* @RETURNS
* returns the amount of damage the enemy deal on a normal attack
*/
float Enemy::getAttackDamage(){
	return attackDamage;
}

/*
* <DESCRIPTION>
* Sets the visual position for the enemy
* This is used for position animation as the default position is controlled by a Transformation object
*
* @PARAMS
* x: float value of the X cord to be set.
* y: float value of the Y cord to be set.
*/
void Enemy::setPosition(float x, float y){
	enemySprite.setPosition(x, y);
}

/*
* @RETURNS
* returns the enemy sprite
*/
Sprite Enemy::getSprite(){
	return enemySprite;
}

/*
* @RETURNS
* returns the type of enemy the object represents.
*/
EnemyType Enemy::getEnemyType(){
	return type;
}

/*
* @RETURNS
* returnst the enemy remaning HP
*/
float Enemy::getHitPoints(){
	return hitPoints;
}

/*
* @RETURNS
* returns the max HP of the enemy
*/
float Enemy::getMaxHitPoints(){
	return maxHitPoints;
}

/*
* <DESCRIPTION>
* Deals damage to the Enemy object.
*
* @PARAMS
* amount: float value that represent the amount of damage the enemy is about to take.
*/
void Enemy::TakeDamage(float amount){
	hitPoints -= amount;
}

/*
* @RETURNS
* returns boolean representing if the enemy is still alive.
*/
bool Enemy::IsAlive(){
	return hitPoints > 0;
}


int Enemy::getXPGrant(){
	return XPGrant;
}
/*
* <DESCRIPTION>
* Sets values for the enemy object depending on it's type.
* Values that are being set: HP, damage, XPGrant, texture
*/
void Enemy::setEnemyValues(){
	switch (type)
	{
		case Skeleton_MELEE:
			if (!enemyTexture.loadFromFile("Textures/PHEnemy.png")){
				throw "TEXTURE LOAD ERROR: Enemy::Skeleton could not load texture.";
			}
			hitPoints = 20;
			XPGrant = 1000;
			attackDamage = 200;
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