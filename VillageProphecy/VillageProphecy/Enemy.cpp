#include "Enemy.h"
#include "EnemySkill_BloodyStrike.h"
#include "EnemySkill_DecayingStrike.h"
#include "EnemySkill_NormalAttack.h"

/*
* <DESCRIPTION>
* Constructor for the Enemy class 
* Calls the setEnemyValues method to set the values for the object.
*
* @PARAMS
* typeOfEnemy: EnemyType enum value that describes the enemy rewards, stats and how it will act
*/
Enemy::Enemy(EnemyType typeOfEnemy, int _level, Texture *enemyTexture) : type(typeOfEnemy), level(_level)
{
	enemySprite.setTexture(*enemyTexture);
	setEnemyStats();	
	setEnemySkills();
}


Enemy::~Enemy()
{
}


/*
* @RETURNS
* returns the amount of damage the enemy deal on a normal attack
*/
int Enemy::getAttackDamage(){
	return attackDamage;
}

/*
* <DESCRIPTION>
* Sets the visual position for the enemy
* This is used for position animation as the default position is controlled by a Transformation object
*
* @PARAMS
* x: int value of the X cord to be set.
* y: int value of the Y cord to be set.
*/
void Enemy::setPosition(int x, int y){
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
int Enemy::getHitPoints(){
	return hitPoints;
}

/*
* @RETURNS
* returns the max HP of the enemy
*/
int Enemy::getMaxHitPoints(){
	return maxHitPoints;
}

/*
* <DESCRIPTION>
* Deals damage to the Enemy object.
*
* @PARAMS
* amount: int value that represent the amount of damage the enemy is about to take.
*/
void Enemy::TakeDamage(int amount){
	hitPoints -= amount;
}

/*
* @RETURNS
* returns boolean representing if the enemy is still alive.
*/
bool Enemy::IsAlive(){
	return hitPoints > 0;
}

/*
* @RETURNS
* returns integer representing the amount of experience points this enemy grants.
*/
int Enemy::getXPGrant(){
	return XPGrant;
}

/*
* @RETURNS
* returns a pointer to this enemy skill vector.
*/
vector<EnemySkill*> *Enemy::getEnemySkills(){
	return &enemySkills;
}


/*
* <DESCRIPTION>
* Sets values for the enemy object depending on it's type.
* Values that are being set: HP, damage, XPGrant, texture
*/
void Enemy::setEnemyStats(){
	switch (type)
	{
		//SET TEXTURES
		case Skeleton_MELEE:			
			hitPoints = 20;
			XPGrant = 1000;
			attackDamage = 4;	
			break;

		case Human_MELEE:
			hitPoints = 75;
			XPGrant = 100;
			attackDamage = 7;
			break;

		case Executioner_BOSS:			
			hitPoints = 300;
			XPGrant = 999;
			attackDamage = 13;	
			break;

		default:
			throw "SET TEXTURE ERROR: Not a valid enemy type was given.";
			break;
	}

	
	LevelBonus();
	maxHitPoints = hitPoints;
}

/*
* <DESCRIPTION>
* Adds level bonus stats to the enemy
*/
void Enemy::LevelBonus(){
	hitPoints += hitPoints * level * levelBonus;
	XPGrant += XPGrant * level * levelBonus;
	attackDamage += attackDamage * level * levelBonus;
}

/*
* <DESCRIPTION>
* Sets the skills of this enemy. The skills the enemy knows is based on the type of the enemy.
*/
void Enemy::setEnemySkills(){
	//all enemies have the normal attack skill
	enemySkills.push_back(new EnemySkill_NormalAttack(this));

	switch (type)
	{
		case Skeleton_MELEE:
			enemySkills.push_back(new EnemySkill_DecayingStrike(this));
			break;

		case Human_MELEE:
			break;

		case Executioner_BOSS:
			enemySkills.push_back(new EnemySkill_DecayingStrike(this));
			enemySkills.push_back(new EnemySkill_BloodyStrike(this));
			break;

		default:
			break;
	}
}