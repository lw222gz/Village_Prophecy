#include "Player.h"

/*
* <DESCRIPTION>
* Player class constructor.
* Initiates the players position, loads the player texture and initiates the players inventory.
* Also loads the AP textures.
*/
Player::Player(TextureLoader *_textures)
	: textures(_textures)
{
	//default position
	playerSprite.setPosition(Vector2f(1000, 450));
	playerSprite.setTexture(*textures->getPlayerTexture());
	//defines inventory
	inventory = new Inventory(textures);

	statsManager = new PlayerStatsManager(&skillManager, textures->getActionPointTexture(), textures->getConsumedActionPointTexture());
}

Player::~Player()
{
}

/*
* @RETURNS
* returns a Vector2f representing the position of the player
*/
Vector2f Player::getPosition(){
	return playerSprite.getPosition();
}

/*
* @RETURNS
* returns a Vector2u representing the size of the player
*/
Vector2u Player::getSize(){
	return playerSprite.getTexture()->getSize();
}

/*
* <DESCRIPTION>
* Sets all current game areas paths refrence to use for collision.
*
* @PARAMS
* areaPaths: a vector contaning all the Path object for the current game area.
*/
void Player::setAreaPaths(vector<Path*> areaPaths){
	avaliblePaths = areaPaths;
}

/*
* <DESCRIPTION>
* Forces the player to the given parameter position.
*
* @PARAMS
* pos: a Vector2f that will set the players position to that value.
*/
void Player::setPlayerPosition(Vector2f pos){
	playerSprite.setPosition(pos);
}

/*
* <DESCRIPTION>
* Sets the borders for the player collides in.
*
* @PARAMS
* size: a Vector2u representing the size of the current game area
*/
void Player::setBorders(Vector2u size){
	borders = size;
}

/*
* @RETURNS
* returns the player sprite
*/
Sprite Player::getSprite(){
	return playerSprite;
}

/*
* @RETURNS
* returns a pointer to the inventory object.
*/
Inventory* Player::InventoryManager(){
	return inventory;
}

/*
* <DESCRIPTION>
* Executes any events that could occur for the player whilst he/she sleeps.
*
* @PARAMS
* hasBurningFirePlace: boolean representing if the player has a burning fireplace at the sleep spot, true if the player has one, otherwise false.
*/
void Player::Sleep(bool hasBurningFirePlace){
	//TODO: effects that can occur during sleep
	statsManager->ResetAP();
	statsManager->playerStaminaAffected(40);
	

	if (!hasBurningFirePlace){
		statsManager->playerHitPointsAffected(-(statsManager->getMaxPlayerHP() * .1));
	}
	else {
		statsManager->playerHitPointsAffected(statsManager->getMaxPlayerHP() * .5);
	}
	/*actionPoints = ACTION_POINTS_MAX;
	playerHitpoints -= 10;
	playerHungerAffected(-40);
	playerMoodAffected(-40);
	playerStaminaAffected(-40);*/
}

/*
* <DESCRIPTION>
* Saves the players position in the normal game mode as it will be a set position during combat phase.
*/
void Player::savePosition(){
	savedPosition = playerSprite.getPosition();
}

/*
* <DESCRIPTION>
* Sets the players position to the saved position
*/
void Player::setToSavedPosition(){
	playerSprite.setPosition(savedPosition);
}

/*
* @RETURNS
* returns a pointer of the players StatsManager object
*/
PlayerStatsManager* Player::StatsManager(){
	return statsManager;
}

/*
* @RETURNS
* returns a pointer of the players SkillManage object
*/
PlayerSkillManager* Player::SkillManager(){
	return &skillManager;
}

/*
* <DESCRIPTION>
* Reflects the player sprite face direction, this method is required due 
* to other scripts should be able to switch the player facing direction
*/
void Player::ReflectPlayerSprite(){
	ReflectSprite(&playerSprite);
}

/*
* <DESCRIPTION>
* Resets the player sprite to face it's default direciton, this method is 
* required due to other scripts should be able to switch the player facing direction 
*/
void Player::ResetPlayerReflectSprite(){
	ResetReflectSprite(&playerSprite);
}

/*
* <DESCRIPTION>
* Updates the players position depending on user input
* Also if the player would enter a path to another area, the area that path leads to is returned.
*
* @PARAMS
*	dir: the direction the player is moving.
*	t: a pointer to a clock timer to calculate the distance the player should move
* @RETURNS
*	Areas enum. If a player entered a new area that area enum value will be returned, otherwise 
*	Areas::None is returned.
*/
Areas Player::playerMove(MoveDirection dir, Time *t){

	float movedDistance = (float)(t->asSeconds() * speed);
	float distanceX = 0;
	float distanceY = 0;

	switch (dir)
	{
		case MoveDirection::Up:
				distanceY = +(movedDistance);	
				if (playerSprite.getPosition().y - distanceY <= 0){
					//TODO: add path collision

					// Player is at the edge of the border thus the player move distance is set to 0
					distanceY = 0;
				}
			
				break;

		case MoveDirection::Down:
				distanceY = -(movedDistance);
				//add height
				if (playerSprite.getPosition().y - distanceY >= borders.y - getSize().y){
					//TODO: add path collision

					// Player is at the edge of the border thus the player move distance is set to 0
					distanceY = 0;
				}
			
				break;

		case MoveDirection::Left:
				distanceX = +(movedDistance);
				if (playerSprite.getPosition().x - distanceX <= 0){

					for (unsigned int i = 0; i < avaliblePaths.size(); i++){
						if (playerSprite.getPosition().y + getSize().y >= avaliblePaths[i]->getPosition().y &&
							playerSprite.getPosition().y <= avaliblePaths[i]->getPosition().y + avaliblePaths[i]->getSize().y &&
							playerSprite.getPosition().x >= avaliblePaths[i]->getPosition().x &&
							playerSprite.getPosition().x <= avaliblePaths[i]->getPosition().x + avaliblePaths[i]->getSize().x){
						
							return avaliblePaths[i]->getNextArea();
						}
					}
					// Player is at the edge of the border thus the player move distance is set to 0
					distanceX = 0;
				}

				ReflectPlayerSprite();
				break;

		case MoveDirection::Right:
				distanceX = -(movedDistance);
				if (playerSprite.getPosition().x - distanceX >= borders.x - getSize().x){

					for (unsigned int i = 0; i < avaliblePaths.size(); i++){
						if (playerSprite.getPosition().y + getSize().y >= avaliblePaths[i]->getPosition().y &&
							playerSprite.getPosition().y <= avaliblePaths[i]->getPosition().y + avaliblePaths[i]->getSize().y &&
							playerSprite.getPosition().x >= avaliblePaths[i]->getPosition().x &&
							playerSprite.getPosition().x <= avaliblePaths[i]->getPosition().x + avaliblePaths[i]->getSize().x){
						
							return avaliblePaths[i]->getNextArea();
						}
					}

					//Player is at the edge of the border thus the player move distance is set to 0
					distanceX = 0;
				}

				ResetPlayerReflectSprite();
				break;

			default:
				throw "Played moved with no direction";
				break;
	}

	//updates the players position
	playerSprite.setPosition(playerSprite.getPosition().x - distanceX, 
							playerSprite.getPosition().y - distanceY);

	return Areas::No_Area;
}