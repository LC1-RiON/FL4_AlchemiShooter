#include "GameScene.h"
#include "Collision.h"
#include <math.h>

#define PIdiv2	(3.14159265359f / 2.0f)

GameScene::GameScene()
{
	x = areaX / 2;
	y = areaY - 100;
	r = 20;
	speed = 4;
	life = 5;
	avoid = 0;

	enemyR = 10;
	enemyCount = 0;
	for (int i = 0; i < ENEMYLIMIT; i++)
	{
		homingTarget[i] = ENEMYLIMIT;
		enemyAlive[i] = false;
	}

	beamR = 6;
	homingLocked = ENEMYLIMIT * 10;
	shotNum = 0;
	reload = 0;
	shotMode = 0;
	for (int i = 0; i < ALLBEAM; i++) {
		shot[i] = false;
	}

	beamLevel[0] = 1;
	beamLevel[1] = 0;
	beamLevel[2] = 0;

	recipeY = 0;
	moveTime = 0;

	wave = 1;
	playTimer = 0;
	afterClear = 0;

	sceneSwitch = false;

	bgY = -1;

	material[0] = 0;
	material[1] = 0;
	material[2] = 0;

	graphbg01[0] = LoadGraph("Graphics/bg01.png");
	graphbg01[1] = LoadGraph("Graphics/bg01.png");
	graphPlayer = LoadGraph("Graphics/player.png");
	GetGraphSize(graphPlayer, &sizePlayerX, &sizePlayerY);
	graphEnemy[0] = LoadGraph("Graphics/enemy01.png");
	graphEnemy[1] = LoadGraph("Graphics/enemy02.png");
	graphEnemy[2] = LoadGraph("Graphics/enemy03.png");
	GetGraphSize(graphEnemy[0], &sizeEnemyX[0], &sizeEnemyY[0]);
	GetGraphSize(graphEnemy[1], &sizeEnemyX[1], &sizeEnemyY[1]);
	GetGraphSize(graphEnemy[2], &sizeEnemyX[2], &sizeEnemyY[2]);
	graphBeam[0] = LoadGraph("Graphics/shotNormal.png");
	graphBeam[1] = LoadGraph("Graphics/shotTwin.png");
	graphBeam[2] = LoadGraph("Graphics/shotHoming.png");
	graphFrame = LoadGraph("Graphics/frame.png");
	graphButton = LoadGraph("Graphics/frame_UI.png");
	graphRecipe = LoadGraph("Graphics/recipe_proto1.1.png");
	graphCursor = LoadGraph("Graphics/recipe_cursor.png");
	graphTrailer = LoadGraph("Graphics/recipe_trailer.png");
	LoadDivGraph("Graphics/font.png", 10, 10, 1, 64, 64, font);
	graphMaterial[0] = LoadGraph("Graphics/enemy01_material.png");
	graphMaterial[1] = LoadGraph("Graphics/enemy02_material.png");
	graphMaterial[2] = LoadGraph("Graphics/enemy03_material.png");

	bgm[0] = LoadSoundMem("Sounds/stage01.mp3");
	bgm[1] = LoadSoundMem("Sounds/stage02.mp3");
	bgm[2] = LoadSoundMem("Sounds/stage03.mp3");
	bgm[3] = LoadSoundMem("Sounds/stageBoss.mp3");
	volume = 255;
	soundShot[0] = LoadSoundMem("Sounds/shotNormal.mp3");
	soundShot[1] = LoadSoundMem("Sounds/shotTwin.mp3");
	soundShot[2] = LoadSoundMem("Sounds/shotHoming.mp3");
}

GameScene::~GameScene()
{
}

void GameScene::FirstInit()
{
	pattern = new EnemyPattern();

	pattern->Setting(wave);

	x = areaX / 2;
	y = areaY - 100;

	for (int i = 0; i < ENEMYLIMIT; i++)
	{
		homingTarget[i] = ENEMYLIMIT;
		enemyAlive[i] = false;
	}
	enemyCount = 0;

	for (int i = 0; i < ALLBEAM; i++) {
		shot[i] = false;
	}
	shotNum = 0;
	reload = 0;

	recipeY = 0;
	moveTime = 0;

	playTimer = 0;
	afterClear = 0;

	volume = 255;
}

void GameScene::Initialize(DataManager* dataManager)
{
	wave++;
	FirstInit();

	dataManager->GiveData(
		bgY, material[0], material[1], material[2],
		beamLevel[0], beamLevel[1], beamLevel[2], beamLevel[3], recipeY,
		mateDigit[0], mateDigit[1], mateDigit[2]);
}

int GameScene::Update(char* keys, char* oldkeys)
{
	if (CheckSoundMem(bgm[wave - 1]) == 0) {
		PlaySoundMem(bgm[wave - 1], DX_PLAYTYPE_LOOP);
	}
	/*自機移動*/
	if (keys[KEY_INPUT_RIGHT] == 1) {
		x += speed;
		if (keys[KEY_INPUT_LSHIFT] == 0 && keys[KEY_INPUT_RSHIFT] == 0) { x += speed; }
		if (x > areaX) {
			x = areaX;
			//if (oldkeys[KEY_INPUT_RIGHT] == 0) {
			//	x = 0;
			//	PlaySoundMem(soundWarp, DX_PLAYTYPE_BACK);
			//}
		}
	}
	if (keys[KEY_INPUT_LEFT] == 1) {
		x -= speed;
		if (keys[KEY_INPUT_LSHIFT] == 0 && keys[KEY_INPUT_RSHIFT] == 0) { x -= speed; }
		if (x < 0) {
			x = 0;
			//if (oldkeys[KEY_INPUT_LEFT] == 0) {
			//	x = areaX;
			//	PlaySoundMem(soundWarp, DX_PLAYTYPE_BACK);
			//}
		}
	}
	if (keys[KEY_INPUT_DOWN] == 1) {
		y += speed;
		if (keys[KEY_INPUT_LSHIFT] == 0 && keys[KEY_INPUT_RSHIFT] == 0) { y += speed; }
		if (y > areaY) { y = areaY; }
	}
	if (keys[KEY_INPUT_UP] == 1) {
		y -= speed;
		if (keys[KEY_INPUT_LSHIFT] == 0 && keys[KEY_INPUT_RSHIFT] == 0) { y -= speed; }
		if (y < 0) { y = 0; }
	}

	/*敵移動*/
	for (int i = 0; i < ENEMYLIMIT; i++)
	{
		if (enemyAlive[i] == true) {
			enemyX[i] += enemyMoveX[i];
			enemyY[i] += enemyMoveY[i];
			enemyMoveTime[i]++;
			// 獣種の横ステップ
			if (enemyType[i] == beast && enemyMoveX[i] == 0 && enemyMoveTime[i] >= 40) {
				enemyMoveTime[i] = 0;
				if (powf(float(x) - float(enemyX[i]), 2.0f) <= 225.0f) {
					if (enemyX[i] * 2 > areaX) {
						enemyMoveX[i] = -4;
					}
					else {
						enemyMoveX[i] = 4;
					}
				}
				else if (enemyX[i] > x) {
					enemyMoveX[i] = -3;
					enemyMoveY[i] = -2;
				}
				else {
					enemyMoveX[i] = 3;
					enemyMoveY[i] = -2;
				}
			}
			else if (enemyType[i] == beast && enemyMoveX[i] != 0 && enemyMoveTime[i] >= 30) {
				enemyMoveTime[i] = 0;
				enemyMoveX[i] = 0;
				enemyMoveY[i] = 2;
			}
			if (enemyType[i] == fairy) {

			}
			if (enemyX[i] >= areaX + enemyR || enemyX[i] <= -enemyR ||
				enemyY[i] >= areaY + enemyR || enemyY[i] <= -enemyR) {
				enemyAlive[i] = false;
				homingLocked = ENEMYLIMIT * 10;
				for (int i = 0; i < ENEMYLIMIT; i++)
				{
					if (enemyAlive[i] == true && homingTarget[i] < homingLocked) {
						homingLocked = homingTarget[i];
					}
				}
			}
		}
	}

	/*モードチェンジ*/
	if (keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0) {
		shotMode++;
		while (shotMode > 2) { shotMode -= 3; }
		while (beamLevel[shotMode] == 0) {
			shotMode++;
			while (shotMode > 2) { shotMode -= 3; }
		}
	}

	/*射撃*/
	if (reload > 0) { reload--; }
	if (keys[KEY_INPUT_SPACE] == 1 && reload <= 0) {
		while (shot[shotNum] == true) { shotNum++; }
		switch (shotMode)
		{
		case normal:
			/* NormalShot */
			beamX[shotNum] = float(x);
			beamY[shotNum] = float(y);
			beamMoveY[shotNum] = -10;
			shot[shotNum] = true;
			beamType[shotNum] = normal;
			power[shotNum++] = 5 + 5 * beamLevel[normal];
			if (shotNum >= ALLBEAM) { shotNum = 0; }
			reload = 8;
			PlaySoundMem(soundShot[normal], DX_PLAYTYPE_BACK);
			break;

		case twin:
			/* TwinShot */
			for (int i = 1; i > -2; i -= 2) {
				beamX[shotNum] = float(x);
				beamY[shotNum] = float(y);
				beamMoveX[shotNum] = float(2 * i);
				beamMoveY[shotNum] = -10;
				shot[shotNum] = true;
				beamType[shotNum] = twin;
				power[shotNum++] = 4 + 4 * beamLevel[twin];
				if (shotNum >= _countof(shot)) { shotNum = 0; }
			}
			reload = 8;
			PlaySoundMem(soundShot[twin], DX_PLAYTYPE_BACK);
			break;

		case homing:
			/* HomingShot */
			beamX[shotNum] = float(x);
			beamY[shotNum] = float(y);
			beamMoveX[shotNum] = 0;
			beamMoveY[shotNum] = 1;
			shot[shotNum] = true;
			beamType[shotNum] = homing;
			power[shotNum] = 15 + 15 * beamLevel[homing];
			forHoming[shotNum++] = 0;
			if (shotNum >= _countof(shot)) { shotNum = 0; }
			reload = 20;
			PlaySoundMem(soundShot[homing], DX_PLAYTYPE_BACK);
			break;
		}
	}

	/*射撃弾*/
	for (int i = 0; i < ALLBEAM; i++)
	{
		if (shot[i] == true) {
			switch (beamType[i])
			{
			case normal:
				beamY[i] += beamMoveY[i];
				break;

			case twin:
				beamX[i] += beamMoveX[i];
				beamY[i] += beamMoveY[i];
				break;

			case homing:
				beamX[i] += beamMoveX[i];
				beamY[i] += beamMoveY[i];
				if (forHoming[i] < 100) { forHoming[i]++; }
				else if (forHoming[i] >= 100 && homingLocked <= ENEMYLIMIT) {
					float distance = sqrtf(
						powf(float(enemyX[homingLocked]) - beamX[i], 2.0f) +
						powf(float(enemyY[homingLocked]) - beamY[i], 2.0f));
					if (homingLocked != ENEMYLIMIT * 9) {
						beamMoveX[i] = float(enemyX[homingLocked] - beamX[i]) * 10.0f / distance;
						beamMoveY[i] = float(enemyY[homingLocked] - beamY[i]) * 10.0f / distance;
					}
				}
				break;
			}
			if (beamY[i] <= -beamR || beamY[i] >= areaY + beamR ||
				beamX[i] <= -beamR || beamX[i] >= areaX + beamR) {
				shot[i] = false;
			}
		}
	}

	/*衝突判定*/
	for (int j = 0; j < ENEMYLIMIT; j++)
	{
		if (enemyAlive[j] == true) {
			for (int i = 0; i < ALLBEAM; i++)
			{
				/*エネミー-ビーム間衝突*/
				if (shot[i] == true &&
					Collision::HitCheck(beamX[i], beamY[i], beamR, enemyX[j], enemyY[j], enemyR) == true) {
					shot[i] = false;
					enemyHP[j] -= power[i];
					if (enemyHP[j] <= 0) {
						enemyAlive[j] = false;
						material[enemyType[j]]++;
						homingLocked = ENEMYLIMIT * 10;
						for (int i = 0; i < ENEMYLIMIT; i++)
						{
							if (enemyAlive[i] == true && homingTarget[i] < homingLocked) {
								homingLocked = homingTarget[i];
							}
						}
					}
				}
			}
			/*エネミー-プレイヤー間衝突*/
			if (avoid <= 0 &&
				Collision::HitCheck(x, y, r, enemyX[j], enemyY[j], enemyR) == true) {
				avoid = 180;
				//life--;
				enemyAlive[j] = false;
				homingLocked = ENEMYLIMIT * 10;
				for (int i = 0; i < ENEMYLIMIT; i++)
				{
					if (enemyAlive[i] == true && homingTarget[i] < homingLocked) {
						homingLocked = homingTarget[i];
					}
				}
			}
		}
	}

	/*素材数の表記*/
	mateDigit[0] = 0;
	digChecker = material[0];
	while (digChecker != 0)
	{
		digChecker /= 10;
		mateDigit[0]++;
	}
	mateDigit[1] = 0;
	digChecker = material[1];
	while (digChecker != 0)
	{
		digChecker /= 10;
		mateDigit[1]++;
	}
	mateDigit[2] = 0;
	digChecker = material[2];
	while (digChecker != 0)
	{
		digChecker /= 10;
		mateDigit[2]++;
	}

	/*経過*/
	playTimer++;
	while (pattern->SpawnCheck(playTimer) == 1)
	{
		pattern->Spawn(
			&enemyType[enemyCount], &enemyHP[enemyCount],
			&enemyX[enemyCount], &enemyY[enemyCount],
			&enemyMoveX[enemyCount], &enemyMoveY[enemyCount]);
		enemyAlive[enemyCount] = true;
		enemyMoveTime[enemyCount] = 0;
		homingTarget[enemyCount] = enemyCount++;
		homingLocked = ENEMYLIMIT * 10;
		for (int i = 0; i < ENEMYLIMIT; i++)
		{
			if (enemyAlive[i] == true && homingTarget[i] < homingLocked) {
				homingLocked = homingTarget[i];
			}
		}
	}
	if (pattern->SpawnCheck(playTimer) == 9999 && homingLocked == ENEMYLIMIT * 10) {
		if (volume > 0) { volume -= 2; }
		else if (volume < 0) { volume = 0; }
		ChangeVolumeSoundMem(volume, bgm[wave - 1]);
		afterClear++;
		if (afterClear >= 140 && sceneSwitch == false) {
			afterClear = 0;
			sceneSwitch = true;
		}
		else if (sceneSwitch == true) {
			moveTime++;
			recipeY = sinf(PIdiv2 * (moveTime / 40.0f)) * areaY;
			if (moveTime >= 40) {
				moveTime = 0;
				sceneSwitch = false;

				StopSoundMem(bgm[wave - 1]);
				return mix;
			}
		}
	}
	if (avoid > 0) { avoid--; }
	bgY += 4;
	if (bgY >= areaY) { bgY -= areaY; }

	return play;
}

void GameScene::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		DrawGraph(areaLeft, areaTop + bgY - areaY * i, graphbg01[i], true);
	}
	if (avoid % 2 == 0) {
		DrawGraph(x - sizePlayerX / 2 + areaLeft, y - sizePlayerY / 2 + areaTop, graphPlayer, true);
	}
	DrawCircle(x + areaLeft, y + areaTop, r, GetColor(128, 128, 255), FALSE);
	for (int i = 0; i < ENEMYLIMIT; i++)
	{
		if (enemyAlive[i] == true) {
			DrawCircle(enemyX[i] + areaLeft, enemyY[i] + areaTop, enemyR, GetColor(179, 207, 255));
			switch (enemyType[i])
			{
			case slime:
				DrawGraph(
					enemyX[i] - sizeEnemyX[slime] / 2 + areaLeft,
					enemyY[i] - sizeEnemyY[slime] / 2 + areaTop,
					graphEnemy[slime], true);
				break;

			case beast:
				DrawGraph(
					enemyX[i] - sizeEnemyX[beast] / 2 + areaLeft,
					enemyY[i] - sizeEnemyY[beast] / 2 + areaTop,
					graphEnemy[beast], true);
				break;

			case fairy:
				DrawGraph(
					enemyX[i] - sizeEnemyX[fairy] / 2 + areaLeft,
					enemyY[i] - sizeEnemyY[fairy] / 2 + areaTop,
					graphEnemy[fairy], true);
				break;
			}
		}
	}
	for (int i = 0; i < ALLBEAM; i++)
	{
		if (shot[i] == true) {
			DrawGraph(int(beamX[i]) + areaLeft - beamR, int(beamY[i]) + areaTop - beamR, graphBeam[beamType[i]], TRUE);
		}
	}
	DrawGraph(areaLeft, recipeY + areaTop - areaY, graphRecipe, true);
	DrawGraph(0, 0, graphFrame, true);
	DrawGraph(0, 0, graphButton, true);
	//for (int i = 0; i < ALLBEAM; i++)
	//{
	//	if (shot[i] == true) {
	//		DrawString(i % 100 * 6 + i / 100, i / 100 * 10, "|", GetColor(255, 255, 255));
	//	}
	//	else {
	//		DrawString(i % 100 * 6 + i / 100, i / 100 * 10, "|", GetColor(0, 0, 0));
	//	}
	//}
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

void GameScene::DataSave(DataManager* dataManager)
{
	dataManager->GetData(
		bgY, material[0], material[1], material[2],
		beamLevel[0], beamLevel[1], beamLevel[2], beamLevel[3],
		recipeY, mateDigit[0], mateDigit[1], mateDigit[2]);
}

void GameScene::GiveData(
	int& bgY_g, int& material01, int& material02, int& material03,
	int& beamLevel01, int& beamLevel02, int& beamLevel03, int& recipeY_g,
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
		recipeY_g = recipeY;
		mateDigit01 = mateDigit[0];
		mateDigit02 = mateDigit[1];
		mateDigit03 = mateDigit[2];
	}
}
