#include "VisualEnemy.h"

//<Summary>
//A visual enemy is an enemy that is in the game world. If the player collides
//with this enemy the combat phase initiates and the player meets the enemies in this
//objects enemyGroup
VisualEnemy::VisualEnemy(EnemyVisualType visualType, Vector2f pos, int level, TextureLoader *_textures)
	: type(visualType), enemyGroupLevel(level), textures(_textures)
{
	setValues();
	ReflectSprite(&enemySprite);
	enemySprite.setPosition(pos);
}


VisualEnemy::~VisualEnemy()
{
}

/*
* @RETURNS
* returns EnemyVisualType enum value representing the enemy type.
*/
EnemyVisualType VisualEnemy::getType(){
	return type;
}

/*
* @RETURNS
* returns integer representing the level of the enemy group.
*/
int VisualEnemy::getEnemyLevel(){
	return enemyGroupLevel;
}

/*
* @RETURNS
* returns sprite of the VisualEnemy
*/
Sprite VisualEnemy::getSprite(){
	return enemySprite;
}

/*
* @RETURNS
* returns pointer to the vecotr of enemies that this visual enemy represents.
*/
vector<Enemy*>* VisualEnemy::getEnemyGroup(){
	return &enemyGroup;
}

/*
* @RETURNS
* returns boolean, true if this visual enemy has collided with the player otherwise false.
*/
bool VisualEnemy::collideWithPlayer(Vector2f playerPos, Vector2u playerSize){
	if (playerPos.x <= enemySprite.getPosition().x + enemyTexture.getSize().x &&
		playerPos.x + playerSize.x >= enemySprite.getPosition().x &&
		playerPos.y <= enemySprite.getPosition().y + enemyTexture.getSize().y &&
		playerPos.y + playerSize.y >= enemySprite.getPosition().y)
		{
			return true;
		}

	return false;
}

/*
* <DESCRIPTION>
* Sets the texture for the visual enemy and calls the method generateMobGroup()
*/
void VisualEnemy::setValues(){
	switch (type)
	{
		//TODO: set textures
		case Skeleton:
			enemyTexture = *textures->getSkeletonTexture();
			break;
			

		case Humans:
			//TODO: add own texture
			enemyTexture = *textures->getHumanSoldierTexture();
			break;

		case Executioner:
			enemyTexture = *textures->getHumanExecutionerTexture();
			break;

		default:
			break;
	}

	enemySprite.setTexture(enemyTexture);
	generareMobGroup();
}

/*
* <DESCRIPTION>
* Generates the mob group the player will face if he collides with this visual enemy.
*/
void VisualEnemy::generareMobGroup(){
	switch (type)
	{
		case Skeleton:
				amountOfMobs = rand() % 3 + 1;

				for (int i = 0; i < amountOfMobs; ++i){
					Enemy *e = new Enemy(EnemyType::Skeleton_MELEE, enemyGroupLevel, textures->getSkeletonTexture());
					enemyGroup.push_back(e);
				}
			break;
			
			
		case Humans:
			amountOfMobs = 2;//rand() % 3 + 1;

			for (int i = 0; i < amountOfMobs; ++i){
				Enemy *e = new Enemy(EnemyType::Human_MELEE, enemyGroupLevel, textures->getHumanSoldierTexture());
				enemyGroup.push_back(e);
			}
			break;

		case Executioner:
			enemyGroup.push_back(new Enemy(EnemyType::Executioner_BOSS, enemyGroupLevel, textures->getHumanExecutionerTexture()));
			enemyGroup.push_back(new Enemy(EnemyType::Human_MELEE, enemyGroupLevel, textures->getHumanSoldierTexture()));
			enemyGroup.push_back(new Enemy(EnemyType::Human_MELEE, enemyGroupLevel, textures->getHumanSoldierTexture()));
			break;

		default:
			throw "Unknown enemy type.";
			break;
	}
}