#pragma once
#include "SFML\Graphics.hpp"

using namespace sf;
class TextureLoader
{
public:
	TextureLoader();
	~TextureLoader();

	Texture *getPlayerTexture();
	Texture *getHumanExecutionerTexture();
	Texture *getHumanSoldierTexture();
	Texture *getSkeletonTexture();

	Texture *getHealStationTexture();
	Texture *getBedTexture();
	Texture *getBurningFirePlaceTexture();
	Texture *getFirePlaceTexture();
	Texture *getPathTexture();
	Texture *getWoodObjectTexture();

	Texture *getEmptyInventorySlotTexture();
	Texture *getOptionPointerTexture();
	Texture *getActionPointTexture();
	Texture *getConsumedActionPointTexture();
	Texture *getInGameMenuTexture();
	Texture *getQuickMenuTexture();
	Texture *getTargetPointerTexture();
	Texture *getWoodSlotTexture();

	Texture *getBackground_GrassTexture();
	Texture *getGameOverTexture();
	Texture *getGameWonTexture();

	Font *getCoolvecticaFont();

private:
	Texture PlayerTexture;
	Texture HumanExecutionerTexture;
	Texture HumanSoldierTexture;
	Texture SkeletonTexture;
	
	Texture HealStationTexture;
	Texture BedTexture;
	Texture BurningFirePlaceTexture;
	Texture FirePlaceTexture;
	Texture PathTexture;
	Texture WoodObjectTexture;

	Texture EmptyInventorySlotTexture;	
	Texture OptionPointerTexture;	
	Texture ActionPointTexture;
	Texture ConsumedActionPointTexture;
	Texture InGameMenuTexture;
	Texture QuickMenuTexture;
	Texture TargetPointerTexture;
	Texture WoodSlotTexture;
	
	Texture Background_GrassTexture;
	Texture GameOverTexture;
	Texture GameWonTexture;

	Font CoolvecticaFont;
};

