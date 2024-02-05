#pragma once
class DataManager
{
private:
	int wave;
	int bgY;
	int material[3];
	int beamLevel[4];
	int recipeY;
	int mateDigit[3];
	int reloadSpeed;
	int shield;
	int warp;
	int bomb;

public:
	void GetData(
		int wave_g, int bgY_g, int material01, int material02, int material03,
		int beamLevel01, int beamLevel02, int beamLevel03, int recipeY_g,
		int mateDigit01, int mateDigit02, int mateDigit03,
		int reloadSpeed_g, int shield_g, int warp_g, int bomb_g
	);

	void GiveData(
		int& wave_g, int& bgY_g, int& material01, int& material02, int& material03,
		int& beamLevel01, int& beamLevel02, int& beamLevel03, int& recipeY_g,
		int& mateDigit01, int& mateDigit02, int& mateDigit03,
		int& reloadSpeed_g, int& shield_g, int& warp_g, int& bomb_g
	);
};

