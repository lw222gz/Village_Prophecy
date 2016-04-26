#pragma once
class PlayerLevel
{
public:
	PlayerLevel(int _Level, int _requiredEXP);
	~PlayerLevel();


private:
	int Level;
	int requiredEXP = 99999;
	float Add_To_Base_HP = 0;

	void SetLevelBonuses();
	

};

