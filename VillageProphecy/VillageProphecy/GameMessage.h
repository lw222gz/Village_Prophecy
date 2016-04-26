#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;
class GameMessage
{
public:
	GameMessage(string message, Vector2f position) : GameMessage(message, position, false) {};
	GameMessage(string message, Vector2f position, bool _isMoving) : GameMessage(message, position, _isMoving, 0) {};
	GameMessage(string message, Vector2f position, bool _isMoving, float _timeToLive);
	~GameMessage();

	void updateMessageTimer(float elapsedTime);
	float getLifeTimePercent();
	Text getMessage();
	void setPosition(Vector2f position);
	void addToCurrentPosition(Vector2f amount);
	float getTextSpeed();
	bool IsMoving();


private:
	Text text;
	Font coolvetica;
	float timeExisted = 0;
	bool isMoving = false;
	const float timeToLive = 0;
};

