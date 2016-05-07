#include "GameMessage.h"

/*
* <DESCRIPTION>
* Third constructor for the GameMessage class.
* Sets timeToLive and isMoving values
* Loads font and sets base values for the text.
*
* @PARAMS
* message: string message that the GameMessage will display.
* position: Vector2f contaning the position for the GameMessage
* _isMoving: boolean, true if the text should move upwards, false if it's position should be static
* _timeToLive: float value representing the amount of seconds the text should be displayed.
* @RETURNS
*
*/
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

/*
* @RETURNS
* returns boolean, true if the message should be moving, false if it's static in position
*/
bool GameMessage::IsMoving(){
	return isMoving;
}

/*
* @RETURNS
* returns the pixel speed per second for a message.
*/
float GameMessage::getTextSpeed(){
	return -70;
}

/*
* <DESCRIPTION>
* Updates the lifetime for a temporary message.
*
* @PARAMS
* elapsedTime: float representing the amount of time passed this game loop iteration.
*/
void GameMessage::updateMessageTimer(float elapsedTime){
	timeExisted += elapsedTime;
}

/*
* @RETURNS
* returns boolean, true if the message should be removed, otherwise false.
*/
float GameMessage::getLifeTimePercent(){
	return timeExisted / timeToLive;
}

/*
* @RETURNS
* returns the Text object of the message
*/
Text GameMessage::getMessage(){
	return text;
}

/*
* <DESCRIPTION>
* Sets the position of the message to a new position.
*
* @PARAMS
* position: Vector2f representing the position to be set for the text.
*/
void GameMessage::setPosition(Vector2f position){
	text.setPosition(position);
}

/*
* <DESCRIPTION>
* Adds position values to the current position of the GameMessage
*
* @PARAMS
* amount: Vector2f that will be added to the current position
*/
void GameMessage::addToCurrentPosition(Vector2f amount){
	text.setPosition(text.getPosition().x + amount.x, text.getPosition().y + amount.y);
}