#pragma once
#include "DxLib.h"
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
	int warp;
	int life;
	int shield;
	int avoid;

	float enemyX[ENEMYLIMIT] = {};
	float enemyY[ENEMYLIMIT] = {};
	float enemyMoveAngle[ENEMYLIMIT] = {};
	float enemyMoveSpeed[ENEMYLIMIT] = {};
	float enemyMoveX[ENEMYLIMIT] = {};
	float enemyMoveY[ENEMYLIMIT] = {};
	int enemyMoveTime[ENEMYLIMIT] = {};
	int enemyType[ENEMYLIMIT] = {};
	int enemyHP[ENEMYLIMIT] = {};
	int homingTarget[ENEMYLIMIT] = {};
	bool enemyAlive[ENEMYLIMIT] = {};
	int animDefeat[ENEMYLIMIT] = {};
	int defeatX[ENEMYLIMIT] = {};
	int defeatY[ENEMYLIMIT] = {};
	bool defeated[ENEMYLIMIT] = {};
	int enemyR;
	int enemyCount;

	float beamX[ALLBEAM] = {};
	float beamY[ALLBEAM] = {};
	int beamR;
	float beamMoveX[ALLBEAM] = {};
	float beamMoveY[ALLBEAM] = {};
	bool shot[ALLBEAM];
	int beamType[ALLBEAM] = {};
	int power[ALLBEAM] = {};
	int forHoming[ALLBEAM] = {};
	int homingLocked;
	int shotNum;
	int reload;
	int reloadSpeed;
	int beamLevel[3] = {};
	int shotMode;
	int bomb;

	int recipeY;
	float moveTime;

	int wave;
	int playTimer;
	int afterClear;

	int material[3] = {};

	int mateDigit[3] = {};
	int digChecker;

	bool sceneSwitch;

	int bgY;

	int graphbg[3][2];
	int graphPlayer;
	int sizePlayerX;
	int sizePlayerY;
	int graphEnemy[3];
	int sizeEnemyX[3];
	int sizeEnemyY[3];
	int graphDefeat[7];
	int graphBeam[3];
	int graphFrame;
	int graphButton;
	int graphRecipe;
	int graphCursor;
	int graphTrailer;
	int font[10];
	int graphMaterial[3];

	int bgm[4];
	int volume;
	int soundShot[3];

public:
	GameScene();

	~GameScene();

	void FirstInit();

	void Initialize(DataManager* dataManager);

	int Update(char* keys, char* oldkeys);

	void Draw();

	void DataSave(DataManager* dataManager);

	void GiveData(
		int& bgY_g, int& material01, int& material02, int& material03,
		int& beamLevel01, int& beamLevel02, int& beamLevel03, int& recipeY_g,
		int& mateDigit01, int& mateDigit02, int& mateDigit03
	);

	float ConvertToRadian(float angle) { return DX_PI_F * angle / 180.0f; }
};

