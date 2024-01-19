#include "DataManager.h"

void DataManager::GetData(int bgY_g, int material01, int material02, int material03, int beamLevel01, int beamLevel02, int beamLevel03, int beamLevel04, int recipeY_g, int mateDigit01, int mateDigit02, int mateDigit03)
{
	bgY = bgY_g;
	material[0] = material01;
	material[1] = material02;
	material[2] = material03;
	beamLevel[0] = beamLevel01;
	beamLevel[1] = beamLevel02;
	beamLevel[2] = beamLevel03;
	beamLevel[3] = beamLevel04;
	recipeY = recipeY_g;
	mateDigit[0] = mateDigit01;
	mateDigit[1] = mateDigit02;
	mateDigit[2] = mateDigit03;
}

void DataManager::GiveData(int& bgY_g, int& material01, int& material02, int& material03, int& beamLevel01, int& beamLevel02, int& beamLevel03, int& beamLevel04, int& recipeY_g, int& mateDigit01, int& mateDigit02, int& mateDigit03)
{
	bgY_g = bgY;
	material01 = material[0];
	material02 = material[1];
	material03 = material[2];
	beamLevel01 = beamLevel[0];
	beamLevel02 = beamLevel[1];
	beamLevel03 = beamLevel[2];
	beamLevel04 = beamLevel[3];
	recipeY_g = recipeY;
	mateDigit01 = mateDigit[0];
	mateDigit02 = mateDigit[1];
	mateDigit03 = mateDigit[2];
}