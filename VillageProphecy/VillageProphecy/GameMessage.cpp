#include "GameMessage.h"


GameMessage::GameMessage(string message, Vector2f position)
{
	text.setString(message);
	text.setPosition(position);

	if (!coolvetica.loadFromFile("Textures/coolvetica.ttf")){
		throw "FONT LOAD ERROR: could not load coolvetica.ttf correctly.";
	}

	//Text settings
	text.setFont(coolvetica);
	text.setCharacterSize(24);
	text.setColor(Color::Black);
}

GameMessage::GameMessage(string message, Vector2f position, float _timeToLive)
	: timeToLive(_timeToLive)
{
	text.setString(message);
	text.setPosition(position);

	if (!coolvetica.loadFromFile("Textures/coolvetica.ttf")){
		throw "FONT LOAD ERROR: could not load coolvetica.ttf correctly.";
	}

	//Text settings
	text.setFont(coolvetica);
	text.setCharacterSize(24);
	text.setColor(Color::Black);
}


GameMessage::~GameMessage()
{
}


void GameMessage::updateMessageTimer(float elapsedTime){
	timeExisted += elapsedTime;
}

//returns true if the message is to be removed.
float GameMessage::getLifeTimePercent(){
	return timeExisted / timeToLive;
}

Text GameMessage::getMessage(){
	return text;
}

void GameMessage::setPosition(Vector2f position){
	text.setPosition(position);
}

void GameMessage::addToCurrentPosition(Vector2f amount){
	text.setPosition(text.getPosition().x + amount.x, text.getPosition().y + amount.y);
}