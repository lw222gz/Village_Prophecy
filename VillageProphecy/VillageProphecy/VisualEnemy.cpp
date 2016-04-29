#include "VisualEnemy.h"

//<Summary>
//A visual enemy is an enemy that is in the game world. If the player collides
//with this enemy the combat phase initiates and the player meets the enemies in this
//objects enemyGroup
VisualEnemy::VisualEnemy(EnemyVisualType visualType, Vector2f pos) : type(visualType)
{
	enemySprite.setPosition(pos);
	setValues();
}


VisualEnemy::~VisualEnemy()
{
}

Sprite VisualEnemy::getSprite(){
	return enemySprite;
}

vector<Enemy*>* VisualEnemy::getEnemyGroup(){
	return &enemyGroup;
}


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

//sets texutre for a visual enemy and sets the enemyGroup vector
void VisualEnemy::setValues(){
	switch (type)
	{
		case Skeleton:
			if (!enemyTexture.loadFromFile("Textures/PHEnemy.png")){
				throw "TEXTURE LOAD ERROR: Visual enemy texture Skeleton could not load.";
			}
			break;
			

		case Humans:
			//TODO: add own texture
			if (!enemyTexture.loadFromFile("Textures/PHEnemy.png")){
				throw "TEXTURE LOAD ERROR: Visual enemy texture Skeleton could not load.";
			}
			break;

		default:
			break;
	}

	enemySprite.setTexture(enemyTexture);
	generareMobGroup();
}


void VisualEnemy::generareMobGroup(){
	switch (type)
	{
		case Skeleton:{
				//TODO:Add enemies to the enemygrou vector
				srand(time(NULL));
				amountOfMobs = 1;//rand() % 3 + 1;

				for (int i = 0; i < amountOfMobs; ++i){
					Enemy *e = new Enemy(EnemyType::Skeleton_MELEE);
					enemyGroup.push_back(e);
				}
			break;
			}
			
		case Humans:
			break;
		default:
			break;
	}
}