#pragma once
class DataManager
{
private:
	int bgY;
	int material[3];
	int beamLevel[4];
	int recipeY;
	int mateDigit[3];

public:
	void GetData(
		int bgY_g, int material01, int material02, int material03,
		int beamLevel01, int beamLevel02, int beamLevel03, int beamLevel04, int recipeY_g,
		int mateDigit01, int mateDigit02, int mateDigit03
	);

	void GiveData(
		int& bgY_g, int& material01, int& material02, int& material03,
		int& beamLevel01, int& beamLevel02, int& beamLevel03, int& beamLevel04, int& recipeY_g,
		int& mateDigit01, int& mateDigit02, int& mateDigit03
	);
};

