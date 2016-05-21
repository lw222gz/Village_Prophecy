#include "IGameArea.h"

/*
* <DESCRIPTION>
* returns random cordes between the interval of 
* (pathSize + spawnIndent) to (areaSize - pathSize - textureSize - spawnIndent)
*
* @PARAMS
* areaSize: Vector2u representing the size of the area the cords are gonna be randomized for.
* pathSize: Vector2u representing the size of the path texture
* textureSize: Vector2u representing the size of the texture for the object that is getting random cords.
*
* @RETURNS
* returns a Vector2f contaning random cord between a set interval depending on parameter values.
* This has to be a Vector2f as the Sprite class does not have a overload method for Vector2u when seting the 
* position of a sprite.
*/
Vector2f IGameArea::getRandomCords(Vector2u areaSize, Vector2u pathSize, Vector2u textureSize)
{
	//formula for random number between two values
	// (max - min + 1) + min; source : http://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
	int max = areaSize.x - pathSize.x - textureSize.x - spawnIndent;
	int min = pathSize.x + spawnIndent;

	float x = rand() % (max - min + 1) + min;

	max = areaSize.y - pathSize.y - textureSize.y - spawnIndent;
	min = pathSize.y + spawnIndent;

	float y = rand() % (max - min + 1) + min;

	return Vector2f(x, y);
}