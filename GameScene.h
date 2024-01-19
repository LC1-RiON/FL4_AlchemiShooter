#pragma once
#include "DxLib.h"
//#include "MixScene.h"
#include "DataManager.h"
#include "EnemyPattern.h"
class GameScene
{
private:
	static const int ENEMYLIMIT = 100;
	static const int areaLeft = 100;
	static const int areaTop = 10;
	static const int areaX = 650;
	static const int areaY = 700;
	static const int ALLBEAM = 500;

private:
	EnemyPattern* pattern = nullptr;

	int x;
	int y;
	int r;
	int speed;
	int life;
	int avoid;

	int enemyX[ENEMYLIMIT] = {};
	int enemyY[ENEMYLIMIT] = {};
	int enemyMoveX[ENEMYLIMIT] = {};
	int enemyMoveY[ENEMYLIMIT] = {};
	int enemyType[ENEMYLIMIT] = {};
	int enemyHP[ENEMYLIMIT] = {};
	int homingTarget[ENEMYLIMIT] = {};
	bool enemyAlive[ENEMYLIMIT] = {};
	int enemyR;
	int enemyCount;

	float beamX[ALLBEAM];
	float beamY[ALLBEAM];
	int beamR;
	float beamMoveX[ALLBEAM];
	float beamMoveY[ALLBEAM];
	bool shot[ALLBEAM];
	int beamType[ALLBEAM];
	int power[ALLBEAM];
	int forHoming[ALLBEAM];
	int homingLocked;
	int shotNum;
	int reload;
	int beamLevel[4] = {};
	int shotMode;

	int recipeY;
	float moveTime;

	int wave;
	int playTimer;
	int afterClear;

	int material[3] = {};

	double powerX;
	double powerY;

	int mateDigit[3] = {};
	int digChecker;

	bool sceneSwitch;

	int bgY;

	int graphbg01[2];
	int graphPlayer;
	int sizePlayerX;
	int sizePlayerY;
	int graphEnemy01;
	int sizeEnemyX;
	int sizeEnemyY;
	int graphFrame;
	int graphButton;
	int graphRecipe;
	int graphCursor;
	int graphTrailer;
	int font[10];
	int graphMaterial01;

	int soundShot;

public:
	GameScene();

	~GameScene();

	void FirstInit();

	void Initialize(DataManager* dataManager);
	//void Initialize(MixScene* mixScene);

	int Update(char* keys, char* oldkeys);

	void Draw();

	void DataSave(DataManager* dataManager);

	void GiveData(
		int& bgY_g, int& material01, int& material02, int& material03,
		int& beamLevel01, int& beamLevel02, int& beamLevel03, int& beamLevel04, int& recipeY_g,
		int& mateDigit01, int& mateDigit02, int& mateDigit03
	);
};

