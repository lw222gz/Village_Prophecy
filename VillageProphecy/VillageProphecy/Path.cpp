#include "Path.h"

//TODO: optimize contrsuctros
Path::Path(Areas area, Direction dir) : leadsTo(area), direction(dir){
	//Loads path texture
	if (!pathTexture.loadFromFile("Textures/PHRoad.png")){
		throw "Error loading Path texture.";
	}
	pathSprite.setTexture(pathTexture);
	//TODO: generate random position
	pathSprite.setPosition(120, 120);
}

Path::Path(Areas area, Direction dir, Vector2f position) : leadsTo(area), direction(dir){
	//Loads path texture
	if (!pathTexture.loadFromFile("Textures/PHRoad.png")){
		throw "Error loading Path texture.";
	}
	pathSprite.setTexture(pathTexture);

	//Position modifing depending on what direction the path leads to.
	if (dir == Direction::East || dir == Direction::West){

		position = Vector2f(position.x, position.y - pathTexture.getSize().y / 2);

		if (dir == Direction::East){
			position = Vector2f(position.x - pathTexture.getSize().x, position.y);
		}		
	}
	else if (dir == Direction::South){
		position = Vector2f(position.x - pathTexture.getSize().x / 2, position.y - pathTexture.getSize().y);
	}

	pathSprite.setPosition(position);
}

Path::~Path()
{
}

Vector2f Path::getPosition(){
	return pathSprite.getPosition();
}

Sprite Path::getSprite(){
	return pathSprite;
}

Vector2u Path::getSize(){
	return pathTexture.getSize();
}

Areas Path::getNextArea(){
	return leadsTo;
}

Direction Path::getDirection(){
	return direction;
}