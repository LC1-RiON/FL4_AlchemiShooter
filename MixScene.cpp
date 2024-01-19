#include "MixScene.h"
#include "enumeration.h"
#include <math.h>

#define PIdiv2	(3.14159265359f / 2.0f)

MixScene::MixScene()
{
	bgY = -1;

	sceneSwitch = false;

	recipeY = 0;
	moveTime = 0;

	graphbg01[0] = LoadGraph("Graphics/bg01.png");
	graphbg01[1] = LoadGraph("Graphics/bg01.png");
	graphPlayer = LoadGraph("Graphics/player.png");
	GetGraphSize(graphPlayer, &sizePlayerX, &sizePlayerY);
	graphRecipe = LoadGraph("Graphics/recipe_proto1.1.png");
	graphCursor = LoadGraph("Graphics/recipe_cursor.png");
	graphFrame = LoadGraph("Graphics/frame.png");
	graphButton = LoadGraph("Graphics/frame_UI.png");
	graphMaterial01 = LoadGraph("Graphics/enemy01_material.png");
	LoadDivGraph("Graphics/font.png", 10, 10, 1, 64, 64, font);
}

MixScene::~MixScene()
{
}

void MixScene::FirstInit()
{
	sceneSwitch = false;
}

void MixScene::Initialize(DataManager* dataManager)
{
	FirstInit();

	dataManager->GiveData(
		bgY, material[0], material[1], material[2],
		beamLevel[0], beamLevel[1], beamLevel[2], beamLevel[3], recipeY,
		mateDigit[0], mateDigit[1], mateDigit[2]);
}
//void MixScene::Initialize(GameScene* gameScene)
//{
//	FirstInit();
//
//	gameScene->GiveData(
//		bgY, material[0], material[1], material[2],
//		beamLevel[0], beamLevel[1], beamLevel[2], beamLevel[3], recipeY,
//		mateDigit[0], mateDigit[1], mateDigit[2]);
//}

int MixScene::Update(char* keys, char* oldkeys)
{
	bgY += 4;
	if (bgY >= areaY) { bgY -= areaY; }
	/*‰Î—Í‹­‰»*/
	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
		if (material[0] >= 15) {
			material[0] -= 15;
			beamLevel[normal]++;
		}
	}
	if (sceneSwitch == false && keys[KEY_INPUT_Z] == 1 && oldkeys[KEY_INPUT_Z] == 0) {
		sceneSwitch = true;
		///*‘å—Ê‚Ì‰Šú‰»ˆ—*/
		//x = areaX / 2;
		//y = areaY - 100;

		//for (int i = 0; i < ENEMYLIMIT; i++)
		//{
		//	homingTarget[i] = ENEMYLIMIT;
		//	enemyAlive[i] = false;
		//}
		//enemyCount = 0;

		//for (int i = 0; i < ALLBEAM; i++) {
		//	shot[i] = false;
		//}
		//shotNum = 0;
		//reload = 0;
	}
	else if (sceneSwitch == true) {
		moveTime++;
		recipeY = cosf(PIdiv2 * (moveTime / 40.0f)) * areaY;
		if (moveTime >= 40) {
			moveTime = 0;
			//pattern->Setting(++wave);
			sceneSwitch = false;

			//playTimer = 0;
			//afterClear = 0;

			recipeY = 0;

			return play;
		}
	}
	//if (keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0 && material[0] >= 15) {
	//	material[0] -= 15;
	//	beamLevel[normal]++;
	//}
	//if (keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0 && material[1] >= 15) {
	//	material[1] -= 15;
	//	beamLevel[right]++;
	//	beamLevel[left]++;
	//}
	//if (keys[KEY_INPUT_D] == 1 && oldkeys[KEY_INPUT_D] == 0 && material[2] >= 15) {
	//	material[2] -= 15;
	//	beamLevel[homing]++;
	//}

	return mix;
}

void MixScene::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(areaLeft, areaTop + bgY - areaY * i, graphbg01[i], true);
	}
	DrawGraph(areaX / 2 - sizePlayerX / 2 + areaLeft, areaY - 100 - sizePlayerY / 2 + areaTop, graphPlayer, true);
	DrawGraph(areaLeft, recipeY + areaTop - areaY, graphRecipe, true);
	if (sceneSwitch == false) {
		DrawGraph(areaLeft, areaTop, graphCursor, true);
	}
	//if (wave == 2) {
	//	DrawGraph(areaLeft, recipeY + areaTop - areaY, graphTrailer, true);
	//}
	DrawGraph(0, 0, graphFrame, true);
	DrawGraph(0, 0, graphButton, true);
	DrawGraph(852, 20, graphMaterial01, true);
	for (int i = 0; i < mateDigit[0]; i++)
	{
		DrawExtendGraph(900 - 32 * i, 84, 932 - 32 * i, 116, font[material[0] / int(pow(10, i)) % 10], true);
	}
	if (mateDigit[0] == 0) {
		DrawExtendGraph(900, 84, 932, 116, font[0], true);
	}
	for (int i = 0; i < mateDigit[1]; i++)
	{
		DrawExtendGraph(1000 - 32 * i, 84, 1032 - 32 * i, 116, font[material[0] / int(pow(10, i)) % 10], true);
	}
	if (mateDigit[1] == 0) {
		DrawExtendGraph(1000, 84, 1032, 116, font[0], true);
	}
	for (int i = 0; i < mateDigit[2]; i++)
	{
		DrawExtendGraph(1100 - 32 * i, 84, 1132 - 32 * i, 116, font[material[0] / int(pow(10, i)) % 10], true);
	}
	if (mateDigit[2] == 0) {
		DrawExtendGraph(1100, 84, 1132, 116, font[0], true);
	}
}

void MixScene::DataSave(DataManager* dataManager)
{
	dataManager->GetData(
		bgY, material[0], material[1], material[2],
		beamLevel[0], beamLevel[1], beamLevel[2], beamLevel[3],
		recipeY, mateDigit[0], mateDigit[1], mateDigit[2]);
}

void MixScene::GiveData(
	int& bgY_g, int& material01, int& material02, int& material03,
	int& beamLevel01, int& beamLevel02, int& beamLevel03, int& beamLevel04, int& recipeY_g,
	int& mateDigit01, int& mateDigit02, int& mateDigit03
)
{
	if (bgY >= 0) {
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
}
