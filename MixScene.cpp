#include "MixScene.h"
#include "enumeration.h"
#include <math.h>

#define DX_DIV_PI_F	(3.14159265359f / 2.0f)

MixScene::MixScene()
{
	bgY = -1;

	reloadSpeed = 0;
	shield = 0;
	warp = 0;
	bomb = 0;

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
	graphMaterial[0] = LoadGraph("Graphics/enemy01_material.png");
	graphMaterial[1] = LoadGraph("Graphics/enemy02_material.png");
	graphMaterial[2] = LoadGraph("Graphics/enemy03_material.png");
	LoadDivGraph("Graphics/font.png", 10, 10, 1, 64, 64, font);
	bgmMix = LoadSoundMem("Sounds/mixing.mp3");
	volume = 255;
	soundCursor = LoadSoundMem("Sounds/cursor.mp3");
	soundMixUp = LoadSoundMem("Sounds/mixUp.mp3");
	soundError = LoadSoundMem("Sounds/mixError.mp3");
}

MixScene::~MixScene()
{
}

void MixScene::FirstInit()
{
	sceneSwitch = false;
	volume = 255;
	ChangeVolumeSoundMem(volume, bgmMix);
}

void MixScene::Initialize(DataManager* dataManager)
{
	FirstInit();

	dataManager->GiveData(
		bgY, material[0], material[1], material[2],
		beamLevel[0], beamLevel[1], beamLevel[2], recipeY,
		mateDigit[0], mateDigit[1], mateDigit[2],
		reloadSpeed, shield, warp, bomb);
}

int MixScene::Update(char* keys, char* oldkeys)
{
	if (CheckSoundMem(bgmMix) == 0) { PlaySoundMem(bgmMix, DX_PLAYTYPE_BACK); }
	bgY += 4;
	if (bgY >= areaY) { bgY -= areaY; }
	/*ÉJÅ[É\Éãà⁄ìÆ*/
	if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0) {
		PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
		cursor[1]--;
		while (cursor[1] < 0) { cursor[1] += 4; }
	}
	if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0) {
		PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
		cursor[1]++;
		while (cursor[1] > 3) { cursor[1] -= 4; }
	}
	if (keys[KEY_INPUT_LEFT] == 1 && oldkeys[KEY_INPUT_LEFT] == 0) {
		PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
		cursor[0]--;
		while (cursor[0] < 0) { cursor[0] += 2; }
	}
	if (keys[KEY_INPUT_RIGHT] == 1 && oldkeys[KEY_INPUT_RIGHT] == 0) {
		PlaySoundMem(soundCursor, DX_PLAYTYPE_BACK);
		cursor[0]++;
		while (cursor[0] > 1) { cursor[0] -= 2; }
	}
	if (cursor[0] == 0 && cursor[1] == 3) {
		cursor[1] = 2;
		if (keys[KEY_INPUT_DOWN] == 1) { cursor[1] = 0; }
	}
	/*ã≠âª*/
	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
		if (cursor[0] == 0 && cursor[1] == 0) {
			if (material[0] >= 30) {
				PlaySoundMem(soundMixUp, DX_PLAYTYPE_BACK);
				material[0] -= 30;
				beamLevel[normal]++;
			}
			else {
				PlaySoundMem(soundError, DX_PLAYTYPE_BACK);
			}
		}
		else if (cursor[0] == 0 && cursor[1] == 1) {
			if (material[1] >= 15) {
				PlaySoundMem(soundMixUp, DX_PLAYTYPE_BACK);
				material[1] -= 10;
				beamLevel[twin]++;
			}
			else {
				PlaySoundMem(soundError, DX_PLAYTYPE_BACK);
			}
		}
		else if (cursor[0] == 0 && cursor[1] == 2) {
			if (material[2] >= 15) {
				PlaySoundMem(soundMixUp, DX_PLAYTYPE_BACK);
				material[2] -= 10;
				beamLevel[homing]++;
			}
			else {
				PlaySoundMem(soundError, DX_PLAYTYPE_BACK);
			}
		}
		else if (cursor[0] == 1 && cursor[1] == 0) {
			if (material[0] >= 20 && material[1] >= 15) {
				PlaySoundMem(soundMixUp, DX_PLAYTYPE_BACK);
				material[0] -= 15;
				material[1] -= 15;
				reloadSpeed++;
			}
			else {
				PlaySoundMem(soundError, DX_PLAYTYPE_BACK);
			}
		}
		else if (cursor[0] == 1 && cursor[1] == 1) {
			if (material[0] >= 20 && material[2] >= 10) {
				PlaySoundMem(soundMixUp, DX_PLAYTYPE_BACK);
				material[0] -= 20;
				material[2] -= 10;
				shield++;
			}
			else {
				PlaySoundMem(soundError, DX_PLAYTYPE_BACK);
			}
		}
		else if (cursor[0] == 1 && cursor[1] == 2) {
			if (material[1] >= 15 && material[2] >= 10) {
				PlaySoundMem(soundMixUp, DX_PLAYTYPE_BACK);
				material[1] -= 15;
				material[2] -= 10;
				warp++;
			}
			else {
				PlaySoundMem(soundError, DX_PLAYTYPE_BACK);
			}
		}
		else if (cursor[0] == 1 && cursor[1] == 3) {
			if (material[0] >= 20 && material[1] >= 15 && material[2] >= 10) {
				PlaySoundMem(soundMixUp, DX_PLAYTYPE_BACK);
				material[0] -= 20;
				material[1] -= 15;
				material[2] -= 10;
				bomb++;
			}
			else {
				PlaySoundMem(soundError, DX_PLAYTYPE_BACK);
			}
		}
	}
	if (sceneSwitch == false && keys[KEY_INPUT_Z] == 1 && oldkeys[KEY_INPUT_Z] == 0) {
		sceneSwitch = true;
	}
	else if (sceneSwitch == true) {
		if (volume > 0) { volume -= 7; }
		else if (volume < 0) { volume = 0; }
		ChangeVolumeSoundMem(volume, bgmMix);
		moveTime++;
		recipeY = cosf(DX_DIV_PI_F * (moveTime / 40.0f)) * areaY;
		if (moveTime >= 40) {
			moveTime = 0;
			sceneSwitch = false;

			recipeY = 0;

			StopSoundMem(bgmMix);
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
		DrawGraph(294 * cursor[0] + 138, 108 * cursor[1] + 48, graphCursor, true);
	}
	DrawGraph(0, 0, graphFrame, true);
	DrawGraph(0, 0, graphButton, true);
	if (material[0] > 0) { DrawGraph(852, 20, graphMaterial[0], true); }
	if (material[1] > 0) { DrawGraph(952, 20, graphMaterial[1], true); }
	if (material[2] > 0) { DrawGraph(1052, 20, graphMaterial[2], true); }
	for (int i = 0; i < mateDigit[0]; i++)
	{
		DrawExtendGraph(900 - 32 * i, 84, 932 - 32 * i, 116, font[material[0] / int(pow(10, i)) % 10], true);
	}
	if (mateDigit[0] == 0) {
		//DrawExtendGraph(900, 84, 932, 116, font[0], true);
	}
	for (int i = 0; i < mateDigit[1]; i++)
	{
		DrawExtendGraph(1000 - 32 * i, 84, 1032 - 32 * i, 116, font[material[1] / int(pow(10, i)) % 10], true);
	}
	if (mateDigit[1] == 0) {
		//DrawExtendGraph(1000, 84, 1032, 116, font[0], true);
	}
	for (int i = 0; i < mateDigit[2]; i++)
	{
		DrawExtendGraph(1100 - 32 * i, 84, 1132 - 32 * i, 116, font[material[2] / int(pow(10, i)) % 10], true);
	}
	if (mateDigit[2] == 0) {
		//DrawExtendGraph(1100, 84, 1132, 116, font[0], true);
	}
}

void MixScene::DataSave(DataManager* dataManager)
{
	dataManager->GetData(
		bgY, material[0], material[1], material[2],
		beamLevel[0], beamLevel[1], beamLevel[2],
		recipeY, mateDigit[0], mateDigit[1], mateDigit[2],
		reloadSpeed, shield, warp, bomb);
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
