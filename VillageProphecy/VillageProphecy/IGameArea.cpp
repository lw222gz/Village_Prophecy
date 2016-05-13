#include "IGameArea.h"

Vector2f IGameArea::getRandomCords(int areaWidth, int areaHeight, 
								  float textureWidth, float textureHeight)
{
	float x = rand() % (areaWidth - (int)textureWidth);
	float y = rand() % (areaHeight - (int)textureHeight);
	return Vector2f(x, y);
}