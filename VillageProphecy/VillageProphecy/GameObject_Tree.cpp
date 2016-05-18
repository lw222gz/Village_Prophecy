#include "GameObject_Tree.h"

/*
* <DESCRIPTION>
* Constructor for the GameObject_Tree class.
* Sets base values.
*
* @PARAMS
* pos: Vector2f positon of the game object
* _TreeTexture: pointer to the texture for the tree object.
*/
GameObject_Tree::GameObject_Tree(Vector2f pos, Texture *_TreeTexture)
{
	objectSprite.setPosition(pos);
	objectSprite.setTexture(*_TreeTexture);
	triggerType = Harvest;
}


GameObject_Tree::~GameObject_Tree()
{
}



/*
* @RETURNS
* returns the object sprite
*/
Sprite GameObject_Tree::getSprite(){
	return objectSprite;
}

/*
* @RETURNS
* returns the object trigger type
*/
TriggerType GameObject_Tree::getTriggerType(){
	return triggerType;
}

/*
* @RETURNS
* returns the object type
*/
GameObjectType GameObject_Tree::getObjectType(){
	return Tree;
}

//TODO: <optimize> plan is to remove this method from the base class.
MaterialList *GameObject_Tree::MaterialListManager(){
	return NULL;
}

//TODO: <optimize> plan is to remove this method from the base class.
void GameObject_Tree::completeConstruction(){
	return;
}

//TODO: <optimize> plan is to remove this method from the base class.
void GameObject_Tree::setOnFire(){
	return;
}