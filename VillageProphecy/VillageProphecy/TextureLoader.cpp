#include "TextureLoader.h"

//Loads every texture for the game
//TODO: Break all texutres up to diffrent texture classes 
//i.e. inventoryTextures, objectTextures, backgroundTextures etc.

/*
* <DESCRIPTION>
* Loads in ALL textures for the game, if any texture doe snot load properly an error is thrown.
*/
TextureLoader::TextureLoader()
{
	if (!PlayerTexture.loadFromFile("Textures/Player.png")){
		throw "Player textures could not load";
	}
	if (!HumanExecutionerTexture.loadFromFile("Textures/HumanExecutioner.png")){
		throw "TEXTURE LOAD ERROR: Enemy::Executioner_BOSS could not load texture.";
	}
	if (!HumanSoldierTexture.loadFromFile("Textures/HumanSoldier.png")){
		throw "TEXTURE LOAD ERROR: Enemy::Human_MELEE could not load texture.";
	}
	if (!SkeletonTexture.loadFromFile("Textures/Skeleton.png")){
		throw "TEXTURE LOAD ERROR: Enemy::Skeleton_MELEE could not load texture.";
	}
	if (!BedTexture.loadFromFile("Textures/Bed.png")){
		throw "TEXTURE LOAD ERROR: Bed texture did not load correctly.";
	}
	if (!BurningFirePlaceTexture.loadFromFile("Textures/BurningFirePlace.png")){
		throw "TEXTURE LOAD ERROR: Burning fireplace texture did not load correctly.";
	}
	if (!FirePlaceTexture.loadFromFile("Textures/FirePlace.png")){
		throw "TEXTURE LOAD ERROR: Fire place texture did not load correctly";
	}
	if (!PathTexture.loadFromFile("Textures/Path.png")){
		throw "TEXTURE LOAD ERROR: Error loading Path texture.";
	}
	if (!WoodObjectTexture.loadFromFile("Textures/WoodObject.png")){
		throw "TEXTURE LOAD ERROR: Game object Wood textures did not load correctly.";
	}
	if (!EmptyInventorySlotTexture.loadFromFile("Textures/EmptyInventorySlot.png")){
		throw "TEXTURE LOAD ERROR: InventorySpot texture did not load correctly.";
	}
	if (!OptionPointerTexture.loadFromFile("Textures/OptionPointer.png")){
		throw "TEXTURE LOAD ERROR: Option poitner texture did not load correctly.";
	}
	if (!ActionPointTexture.loadFromFile("Textures/PHActionPoint.png")){
		throw "TEXTURE LOAD ERROR: Action point texture did not load correctly.";
	}
	if (!ConsumedActionPointTexture.loadFromFile("Textures/PHConsumedActionPoint.png")){
		throw "TEXTURE LOAD ERROR: Consumed Action point texture did not load correctly.";
	}
	if (!InGameMenuTexture.loadFromFile("Textures/PHInGameMenu.png")){
		throw "TEXTURE LOAD ERROR: inGameMenu did not load correctly.";
	}
	if (!QuickMenuTexture.loadFromFile("Textures/QuickMenu.png")){
		throw "TEXTURE LOAD ERROR: quickMenu texture did not load correctly.";
	}
	if (!TargetPointerTexture.loadFromFile("Textures/TargetPointer.png")){
		throw "TEXTURE LOAD ERROR: Could not load target arrow texture.";
	}
	if (!WoodSlotTexture.loadFromFile("Textures/WoodSlotTexture.png")){
		throw "TEXTURE LOAD ERROR: Wood slot texture did not load correctly.";
	}
	if (!Background_GrassTexture.loadFromFile("Textures/Grass.png")){
		throw "TEXTURE LOAD ERROR: Grass background texture did not load correctly.";
	}
	if (!GameOverTexture.loadFromFile("Textures/PHGameOver.png")){
		throw "TEXTURE LOAD ERROR: Game over Texture did not load correctly";
	}
	if (!GameWonTexture.loadFromFile("Textures/PHGameWon.png")){
		throw "TEXTURE LOAD ERROR: won game texture could not load correctly.";
	}
	if (!CoolvecticaFont.loadFromFile("Textures/coolvetica.ttf")){
		throw "FONT LOAD ERROR: could not load coolvetica.ttf correctly.";
	}
}


TextureLoader::~TextureLoader()
{
}

/*
* @RETURNS
* returns pointer to texture for the player
*/
Texture *TextureLoader::getPlayerTexture() {
	return &PlayerTexture;
}

/*
* @RETURNS
* returns pointer to texture for the Huamn Executioner boss
*/
Texture *TextureLoader::getHumanExecutionerTexture(){
	return &HumanExecutionerTexture;
}

/*
* @RETURNS
* returns pointer to texture for the human soldier texture
*/
Texture *TextureLoader::getHumanSoldierTexture(){
	return &HumanSoldierTexture;
}

/*
* @RETURNS
* returns pointer to texture for the skeleton enemy
*/
Texture *TextureLoader::getSkeletonTexture(){
	return &SkeletonTexture;
}

/*
* @RETURNS
* returns pointer to texture for the player bed
*/
Texture *TextureLoader::getBedTexture(){
	return &BedTexture;
}

/*
* @RETURNS
* returns pointer to texture for a burning fireplace
*/
Texture *TextureLoader::getBurningFirePlaceTexture(){
	return &BurningFirePlaceTexture;
}

/*
* @RETURNS
* returns pointer to texture for a fireplace
*/
Texture *TextureLoader::getFirePlaceTexture(){
	return &FirePlaceTexture;
}

/*
* @RETURNS
* returns pointer to texture for the game path
*/
Texture *TextureLoader::getPathTexture(){
	return &PathTexture;
}

/*
* @RETURNS
* returns pointer to texture for the tree object
*/
Texture *TextureLoader::getWoodObjectTexture(){
	return &WoodObjectTexture;
}

/*
* @RETURNS
* returns pointer to texture for an empty inventory slot
*/
Texture *TextureLoader::getEmptyInventorySlotTexture(){
	return &EmptyInventorySlotTexture;
}

/*
* @RETURNS
* returns pointer to texture for arrow displaying current menu option
*/
Texture *TextureLoader::getOptionPointerTexture(){
	return &OptionPointerTexture;
}

/*
* @RETURNS
* returns pointer to texture for a useable action point
*/
Texture *TextureLoader::getActionPointTexture(){
	return &ActionPointTexture;
}

/*
* @RETURNS
* returns pointer to texture for a consumed action point
*/
Texture *TextureLoader::getConsumedActionPointTexture(){
	return &ConsumedActionPointTexture;
}

/*
* @RETURNS
* returns pointer to texture for the in game menu
*/
Texture *TextureLoader::getInGameMenuTexture(){
	return &InGameMenuTexture;
}

/*
* @RETURNS
* returns pointer to texture for the quick menu
*/
Texture *TextureLoader::getQuickMenuTexture(){
	return &QuickMenuTexture;
}

/*
* @RETURNS
* returns pointer to texture for the target arrow displaying the players current target for an attack
*/
Texture *TextureLoader::getTargetPointerTexture(){
	return &TargetPointerTexture;
}

/*
* @RETURNS
* returns pointer to texture for a wood item slot
*/
Texture *TextureLoader::getWoodSlotTexture(){
	return &WoodSlotTexture;
}

/*
* @RETURNS
* returns pointer to texture for the grass background
*/
Texture *TextureLoader::getBackground_GrassTexture(){
	return &Background_GrassTexture;
}

/*
* @RETURNS
* returns pointer to texture for a game over display
*/
Texture *TextureLoader::getGameOverTexture(){
	return &GameOverTexture;
}

/*
* @RETURNS
* returns pointer to texture for a game won displayer
*/
Texture *TextureLoader::getGameWonTexture(){
	return &GameWonTexture;
}

/*
* @RETURNS
* returns pointer to coolvetica font.
*/
Font *TextureLoader::getCoolvecticaFont(){
	return &CoolvecticaFont;
}