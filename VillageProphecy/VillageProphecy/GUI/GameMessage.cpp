#include "GameMessage.h"

/*
* <DESCRIPTION>
* Constructor for the GameMessage class.
* Sets base values.
*
* @PARAMS
* message: string message that the GameMessage will display.
* position: Vector2f contaning the position for the GameMessage
* _timeToLive: float value representing the amount of seconds the text should be displayed.
* font: Font object that decides the font for the text.
* characterSize: size of the characters for the text, this is by default 24.
*/
GameMessage::GameMessage(string message, Vector2f position, float _timeToLive, Font *font, int characterSize)
	: timeToLive(_timeToLive), startPosition(position)
{
	text.setString(message);
	text.setPosition(position);
	
	//Text settings
	text.setFont(*font);
	text.setCharacterSize(characterSize);
	text.setColor(Color::Black);
}


GameMessage::~GameMessage()
{
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

/*
* <DESCRIPTION>
* Calls DrawMessage(RenderWindow *window, float elapsedTime, Transform transformation)
* with an empty Transform object.
*
* @PARAMS
* window: pointer to the game window object
* elapsedTime: float value representing the amount of seconds passed during
* this iteration of the game loop.
*/
void GameMessage::DrawMessage(RenderWindow *window, float elapsedTime){
	Transform trans;
	DrawMessage(window, elapsedTime, trans);
}

/*
* <DESCRIPTION>
* Draws this GameMessage object.
*
* @PARAMS
* window: pointer to the game window object
* elapsedTime: float value representing the amount of seconds passed during
* this iteration of the game loop.
*
* transformation: Transform oject that can contain any set position that should be added or 
* removed to the text current position.
*/
void GameMessage::DrawMessage(RenderWindow *window, float elapsedTime, Transform transformation){
	updateMessageTimer(elapsedTime);

	text.setPosition(startPosition.x, startPosition.y + timeExisted * textSpeed);

	window->draw(text, transformation);
}