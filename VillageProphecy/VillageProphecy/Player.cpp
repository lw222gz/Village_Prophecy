#include "Player.h"


Player::Player()
{
	playerSprite.setPosition(Vector2f(120, 120));

	if (!playerTexture.loadFromFile("Textures/PHPlayer.png")){
		throw "Player textures could not load";
	}
	playerSprite.setTexture(playerTexture);
	//playerSprite.setPosition(position);
}


Player::~Player()
{
}

Vector2f Player::getPosition(){
	return playerSprite.getPosition();
}

void Player::setAreaPaths(vector<Path*> areaPaths){
	avaliblePaths = areaPaths;
}

void Player::setPlayerPosition(Vector2f pos){
	playerSprite.setPosition(pos);
}

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
				distanceY = 0;
			}
			
			break;

	case MoveDirection::Down:
			distanceY = -(movedDistance);
			//add height
			if (playerSprite.getPosition().y - distanceY >= borders.y - playerTexture.getSize().y){
				//TODO: add path collision
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

	return Areas::None;
}

void Player::setBorders(Vector2u size){
	borders = size;
}


Sprite Player::getSprite(){
	return playerSprite;
}
