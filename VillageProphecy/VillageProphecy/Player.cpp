#include "Player.h"


Player::Player()
{
	//default position
	playerSprite.setPosition(Vector2f(1000, 450));

	if (!playerTexture.loadFromFile("Textures/PHPlayer.png")){
		throw "Player textures could not load";
	}
	playerSprite.setTexture(playerTexture);

	//defines inventory
	inventory = new Inventory();
}


Player::~Player()
{
}

//returns the players postion
Vector2f Player::getPosition(){
	return playerSprite.getPosition();
}

//returns the size of the users texture.
Vector2u Player::getSize(){
	return playerTexture.getSize();
}

//Sets the vector for all the avalibel paths in the current game area.
void Player::setAreaPaths(vector<Path*> areaPaths){
	avaliblePaths = areaPaths;
}

//Forces the player to the given vector position.
void Player::setPlayerPosition(Vector2f pos){
	playerSprite.setPosition(pos);
}

//Sets the borders the player will collide against.
void Player::setBorders(Vector2u size){
	borders = size;
}

//returns the players sprite
Sprite Player::getSprite(){
	return playerSprite;
}

//returns a pointer of the inventoryManager object
Inventory* Player::InventoryManager(){
	return inventory;
}

/*
* <DESCRIPTION>: Updates the players position depending on user input
* Also if the player would enter a path to another area, the area that path leads to is returned.
*
* @PARAMS
*	dir = the direction the player is moving.
*	t = a pointer to a clock timer to calculate the distance the player should move
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
			if (playerSprite.getPosition().y - distanceY >= borders.y - playerTexture.getSize().y){
				//TODO: add path collision

				// Player is at the edge of the border thus the player move distance is set to 0
				distanceY = 0;
			}
			
			break;

	case MoveDirection::Left:
			distanceX = +(movedDistance);
			if (playerSprite.getPosition().x - distanceX <= 0){

				for (unsigned int i = 0; i < avaliblePaths.size(); i++){
					if (playerSprite.getPosition().y + playerTexture.getSize().y >= avaliblePaths[i]->getPosition().y &&
						playerSprite.getPosition().y <= avaliblePaths[i]->getPosition().y + avaliblePaths[i]->getSize().y &&
						playerSprite.getPosition().x >= avaliblePaths[i]->getPosition().x &&
						playerSprite.getPosition().x <= avaliblePaths[i]->getPosition().x + avaliblePaths[i]->getSize().x){
						
						return avaliblePaths[i]->getNextArea();
					}
				}
				// Player is at the edge of the border thus the player move distance is set to 0
				distanceX = 0;
			}
			
			break;

	case MoveDirection::Right:
			distanceX = -(movedDistance);
			if (playerSprite.getPosition().x - distanceX >= borders.x - playerTexture.getSize().x){

				for (unsigned int i = 0; i < avaliblePaths.size(); i++){
					if (playerSprite.getPosition().y + playerTexture.getSize().y >= avaliblePaths[i]->getPosition().y &&
						playerSprite.getPosition().y <= avaliblePaths[i]->getPosition().y + avaliblePaths[i]->getSize().y &&
						playerSprite.getPosition().x >= avaliblePaths[i]->getPosition().x &&
						playerSprite.getPosition().x <= avaliblePaths[i]->getPosition().x + avaliblePaths[i]->getSize().x){
						
						return avaliblePaths[i]->getNextArea();
					}
				}

				//Player is at the edge of the border thus the player move distance is set to 0
				distanceX = 0;
			}
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