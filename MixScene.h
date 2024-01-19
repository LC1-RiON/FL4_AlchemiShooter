#pragma once
#include "DxLib.h"
//#include "GameScene.h"
#include "DataManager.h"
class MixScene
{
private:
	static const int areaLeft = 100;
	static const int areaTop = 10;
	static const int areaX = 650;
	static const int areaY = 700;

private:
	int bgY;

	int material[3] = {};

	int beamLevel[4] = {};

	bool sceneSwitch;

	int recipeY;
	float moveTime;

	int mateDigit[3] = {};

	int graphbg01[2];
	int graphPlayer;
	int sizePlayerX;
	int sizePlayerY;
	int graphRecipe;
	int graphCursor;
	int graphFrame;
	int graphButton;
	int graphMaterial01;
	int font[10];

public:
	MixScene();

	~MixScene();

	void FirstInit();

	void Initialize(DataManager* dataManager);
	//void Initialize(GameScene* gameScene);

	int Update(char* keys, char* oldkeys);

	void Draw();

	void DataSave(DataManager* dataManager);

	void GiveData(
		int& bgY_g, int& material01, int& material02, int& material03,
		int& beamLevel01, int& beamLevel02, int& beamLevel03, int& beamLevel04, int& recipeY_g,
		int& mateDigit01, int& mateDigit02, int& mateDigit03
	);
};
