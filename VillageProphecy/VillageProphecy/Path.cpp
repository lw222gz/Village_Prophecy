#include "Path.h"

Path::~Path()
{
}

/*
* <DESCRIPTION>
* Second constructor for the Path class.
* Will have a set position for the path
*
* @PARAMS
* area: Areas enum that represents to what game area the path will lead to.
* dir: Direction enum that represents what direction the path heads towards.
* position: a Vector2f that represents the position the path will be placed at.
*/
Path::Path(Areas area, Direction dir, Vector2f position) : leadsTo(area), direction(dir){
	//Loads path texture
	if (!pathTexture.loadFromFile("Textures/Path.png")){
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

	if (dir == West){
		//reflects the texture
		pathSprite.setOrigin(pathSprite.getLocalBounds().width, 0);
		pathSprite.setScale(-1.f, 1.f);
	}
	

	pathSprite.setPosition(position);
}



/*
* @RETURNS
* returns the position of the path
*/
Vector2f Path::getPosition(){
	return pathSprite.getPosition();
}

/*
* @RETURNS
* returns the path visual sprite
*/
Sprite Path::getSprite(){
	return pathSprite;
}

/*
* @RETURNS
* returns the size of the path
*/
Vector2u Path::getSize(){
	return pathTexture.getSize();
}

/*
* @RETURNS
* returns a Areas enum value that represents the type of area the path leads to.
*/
Areas Path::getNextArea(){
	return leadsTo;
}

/*
* @RETURNS
* returns a Direction enum value that represents the direction the path is heading towards
*/
Direction Path::getDirection(){
	return direction;
}