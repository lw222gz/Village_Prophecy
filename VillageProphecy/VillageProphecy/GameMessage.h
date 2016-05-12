#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;
class GameMessage
{
public:
	GameMessage(string message, Vector2f position) : GameMessage(message, position, 0, 24) {};
	GameMessage(string message, Vector2f position, float _timeToLive, int characterSize = 24);
	~GameMessage();

	
	float getLifeTimePercent();
	Text getMessage();
	void setPosition(Vector2f position);
	void addToCurrentPosition(Vector2f amount);

	void DrawMessage(RenderWindow *window, float elapsedTime);
	void DrawMessage(RenderWindow *window, float elapsedTime, Transform transformation);

private:
	Text text;
	Font coolvetica;
	Vector2f startPosition;
	//speed of the per second.
	float textSpeed = -70;
	float timeExisted = 0;
	const float timeToLive = 0;

	void updateMessageTimer(float elapsedTime);
};

