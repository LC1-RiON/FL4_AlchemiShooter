#include "DxLib.h"
#include <time.h>
#include <math.h>
#include "enumeration.h"
#include "EnemyPattern.h"

#define PI	3.14159265359f
#define PIdiv2	(3.14159265359f / 2.0f)

const char TITLE[] = "AlchemiShooter";

const int WinX = 1280;

const int WinY = 720;

bool InitializeWindow();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウ関係の各初期化
	if (InitializeWindow() == false) { return -1; }

	// ゲーム内変数
	srand(time(NULL));

	int scene = title;
	bool sceneSwitch = false;

	// プレイエリア_x650:y700
	int areaLeft = 100;
	int areaTop = 10;
	int areaX = 650;
	int areaY = 700;

	int x = areaX / 2;
	int y = areaY - 100;
	int r = 20;
	int life = 5;
	int avoid = 0;

	const int ENEMYLIMIT = 100;
	int enemyX[ENEMYLIMIT] = {};
	int enemyY[ENEMYLIMIT] = {};
	int enemyMoveX[ENEMYLIMIT] = {};
	int enemyMoveY[ENEMYLIMIT] = {};
	int enemyType[ENEMYLIMIT] = {};
	int enemyHP[ENEMYLIMIT] = {};
	int homingTarget[ENEMYLIMIT] = {};
	bool enemyAlive[ENEMYLIMIT] = {};
	for (int i = 0; i < ENEMYLIMIT; i++)
	{
		homingTarget[i] = ENEMYLIMIT;
		enemyAlive[i] = false;
	}
	int enemyR = 10;
	int enemyCount = 0;

	EnemyPattern* pattern = new EnemyPattern();
	int wave = 1;
	pattern->Setting(wave);
	int playTimer = 0;
	int afterClear = 0;

	int material[3] = {};

	int mateDigit[3] = {};
	int digChecker;

	const int ALLBEAM = 500;
	float beamX[ALLBEAM];
	float beamY[ALLBEAM];
	int beamR = 5;
	float beamMoveX[ALLBEAM];
	float beamMoveY[ALLBEAM];
	bool shot[ALLBEAM];
	int beamType[ALLBEAM];
	int power[ALLBEAM];
	int forHoming[ALLBEAM];
	int homingLocked = ENEMYLIMIT * 10;
	for (int i = 0; i < ALLBEAM; i++) {
		shot[i] = false;
	}
	int shotNum = 0;
	int reload = 0;
	int beamLevel[4] = { 1, 1, 1, 1 };
	int shotMode = 0;

	double powerX = 0;
	double powerY = 0;

	int recipeY = 0;
	float moveTime = 0;

	// リソース系変数
	int graphTitle[4];
	LoadDivGraph("Graphics/title.png", 4, 4, 1, WinX, WinY, graphTitle);
	int titleFlash = 0;
	const int flashRate = 40;
	int graphbg01[2];
	graphbg01[0] = LoadGraph("Graphics/bg01.png");
	graphbg01[1] = LoadGraph("Graphics/bg01.png");
	int bgY = 0;
	int graphPlayer = LoadGraph("Graphics/player.png");
	int sizePlayerX;
	int sizePlayerY;
	GetGraphSize(graphPlayer, &sizePlayerX, &sizePlayerY);
	int graphEnemy01 = LoadGraph("Graphics/enemy01.png");
	int sizeEnemyX;
	int sizeEnemyY;
	GetGraphSize(graphEnemy01, &sizeEnemyX, &sizeEnemyY);
	int graphFrame = LoadGraph("Graphics/frame.png");
	int graphButton = LoadGraph("Graphics/frame_UI.png");
	int graphRecipe = LoadGraph("Graphics/recipe_proto1.1.png");
	int graphCursor = LoadGraph("Graphics/recipe_cursor.png");
	int graphTrailer = LoadGraph("Graphics/recipe_trailer.png");
	int font[10];
	LoadDivGraph("Graphics/font.png", 10, 10, 1, 64, 64, font);
	int graphMaterial01 = LoadGraph("Graphics/enemy01_material.png");

	int bgm01 = LoadSoundMem("Sounds/stage02_a.mp3");	/*一旦の仮置き*/
	int bgm02 = LoadSoundMem("Sounds/stage02_b.mp3");
	int bgm03 = LoadSoundMem("Sounds/stage03.mp3");
	int bgmBoss = LoadSoundMem("Sounds/stageBoss.mp3");
	int bgmMix = LoadSoundMem("Sounds/mixing.mp3");		/*ループカウント=5175*/
	int loopTime = 0;

	// キーボード入力情報、最新＆前フレーム
	char keys[256] = {};
	char oldkeys[256] = {};

	// ゲームループ
	while (1)
	{
		// 全キーボード入力情報更新
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		GetHitKeyStateAll(keys);

		// 画面リセット
		ClearDrawScreen();

		/*ゲーム処理*/
		// UPDATE
		/*BGM再生*/
		if (CheckSoundMem(bgmMix) == 0) { PlaySoundMem(bgmMix, DX_PLAYTYPE_BACK); }
		else {
			loopTime++;
			if (loopTime >= 3863) {
				loopTime = 0;
				PlaySoundMem(bgmMix, DX_PLAYTYPE_BACK);
			}
		}
		switch (scene)
		{
		case title:
			titleFlash++;
			if (titleFlash >= flashRate * 4) { titleFlash -= (flashRate * 4); }
			for (int i = 0; i < 256; i++)
			{
				if (keys[i] == 1 && oldkeys[i] == 0) {
					scene = play;
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

					for (int i = 0; i < 4; i++)
					{
						beamLevel[i] = 1;
					}

					recipeY = 0;
					moveTime = 0;

					wave = 1;
					pattern->Setting(wave);
					playTimer = 0;
					afterClear = 0;

					material[0] = 0;
					material[1] = 0;
					material[2] = 0;

					break;
				}
			}
			//if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			//}
			break;

		case play:
			/*自機移動*/
			if (keys[KEY_INPUT_RIGHT] == 1) {
				x += 4;
				if (x > areaX) {
					x = areaX;
					//if (oldkeys[KEY_INPUT_RIGHT] == 0) { x = 0; }
				}
			}
			if (keys[KEY_INPUT_LEFT] == 1) {
				x -= 4;
				if (x < 0) {
					x = 0;
					//if (oldkeys[KEY_INPUT_LEFT] == 0) { x = areaX; }
				}
			}
			if (keys[KEY_INPUT_DOWN] == 1) {
				y += 4;
				if (y > areaY) { y = areaY; }
			}
			if (keys[KEY_INPUT_UP] == 1) {
				y -= 4;
				if (y < 0) { y = 0; }
			}

			/*敵移動*/
			for (int i = 0; i < ENEMYLIMIT; i++)
			{
				if (enemyAlive[i] == true) {
					enemyX[i] += enemyMoveX[i];
					enemyY[i] += enemyMoveY[i];
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
			//if (keys[KEY_INPUT_X] == 1 && oldkeys[KEY_INPUT_X] == 0) {
			//	shotMode++;
			//	while (shotMode > 2) { shotMode -= 3; }
			//}
			//if (keys[KEY_INPUT_Z] == 1 && oldkeys[KEY_INPUT_Z] == 0) {
			//	shotMode--;
			//	while (shotMode < 0) { shotMode += 3; }
			//}

			/*射撃*/
			if (reload > 0) { reload--; }
			if (keys[KEY_INPUT_SPACE] == 1 && reload <= 0) {
				while (shot[shotNum] == true) { shotNum++; }
				switch (shotMode)
				{
				case 0:
					/* NormalShot */
					beamX[shotNum] = x;
					beamY[shotNum] = y;
					beamMoveY[shotNum] = -10;
					shot[shotNum] = true;
					beamType[shotNum] = normal;
					power[shotNum++] = 5 + 5 * beamLevel[normal];
					if (shotNum >= ALLBEAM) { shotNum = 0; }
					reload = 8;
					break;

				case 1:
					/* TwinShot */
					for (int i = 1; i > -2; i -= 2) {
						beamX[shotNum] = x;
						beamY[shotNum] = y;
						beamMoveX[shotNum] = 2 * i;
						beamMoveY[shotNum] = -10;
						shot[shotNum] = true;
						if (i > 0) { beamType[shotNum] = right; }
						else { beamType[shotNum] = left; }
						power[shotNum++] = 4 + 4 * beamLevel[right];
						if (shotNum >= _countof(shot)) { shotNum = 0; }
					}
					reload = 8;
					break;

				case 2:
					/* HomingShot */
					beamX[shotNum] = x;
					beamY[shotNum] = y;
					beamMoveX[shotNum] = 0;
					beamMoveY[shotNum] = 1;
					shot[shotNum] = true;
					beamType[shotNum] = homing;
					power[shotNum] = 15 + 15 * beamLevel[homing];
					forHoming[shotNum++] = 0;
					if (shotNum >= _countof(shot)) { shotNum = 0; }
					reload = 20;
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

					case right:
					case left:
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
						powerX = pow(beamX[i] - enemyX[j], 2.0);
						powerY = pow(beamY[i] - enemyY[j], 2.0);
						/*エネミー-ビーム間衝突*/
						if (shot[i] == true && powerX + powerY <= pow(beamR + enemyR, 2.0)) {
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
					powerX = pow(x - enemyX[j], 2.0);
					powerY = pow(y - enemyY[j], 2.0);
					/*エネミー-プレイヤー間衝突*/
					if (avoid <= 0 && powerX + powerY <= pow(r + enemyR, 2.0)) {
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
						scene = mix;
						sceneSwitch = false;
					}
				}
			}
			if (avoid > 0) { avoid--; }
			bgY += 4;
			if (bgY >= areaY) { bgY -= areaY; }
			break;

		case mix:
			bgY += 4;
			if (bgY >= areaY) { bgY -= areaY; }
			/*火力強化*/
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
				if (material[0] >= 15) {
					material[0] -= 15;
					beamLevel[normal]++;
				}
			}
			if (sceneSwitch == false && keys[KEY_INPUT_Z] == 1 && oldkeys[KEY_INPUT_Z] == 0) {
				sceneSwitch = true;
				/*大量の初期化処理*/
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
			}
			else if (sceneSwitch == true) {
				if (wave == 2) {
					scene = title;
					sceneSwitch = false;

					titleFlash = 0;
				}
				moveTime++;
				recipeY = cosf(PIdiv2 * (moveTime / 40.0f)) * areaY;
				if (moveTime >= 40) {
					moveTime = 0;
					pattern->Setting(++wave);
					scene = play;
					sceneSwitch = false;

					playTimer = 0;
					afterClear = 0;

					recipeY = 0;
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
			break;

		case result:
			break;
		}

		// DRAW
		switch (scene)
		{
		case title:
			DrawGraph(0, 0, graphTitle[titleFlash / flashRate], true);
			break;

		case play:
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
					DrawGraph(
						enemyX[i] - sizeEnemyX / 2 + areaLeft,
						enemyY[i] - sizeEnemyY / 2 + areaTop,
						graphEnemy01, true);
				}
			}
			for (int i = 0; i < ALLBEAM; i++)
			{
				if (shot[i] == true) {
					DrawCircle(beamX[i] + areaLeft, beamY[i] + areaTop, beamR, GetColor(255, 255, 255));
				}
			}
			//DrawBox(areaLeft, areaTop, areaLeft + areaX, areaTop + areaY, GetColor(128, 255, 128), FALSE);
			DrawGraph(areaLeft, recipeY + areaTop - areaY, graphRecipe, true);
			if (wave == 2) {
				DrawGraph(areaLeft, recipeY + areaTop - areaY, graphTrailer, true);
			}
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
			break;

		case mix:
			for (int i = 0; i < 2; i++)
			{
				DrawGraph(areaLeft, areaTop + bgY - areaY * i, graphbg01[i], true);
			}
			if (avoid % 2 == 0) {
				DrawGraph(x - sizePlayerX / 2 + areaLeft, y - sizePlayerY / 2 + areaTop, graphPlayer, true);
			}
			DrawGraph(areaLeft, recipeY + areaTop - areaY, graphRecipe, true);
			if (sceneSwitch == false) {
				DrawGraph(areaLeft, areaTop, graphCursor, true);
			}
			if (wave == 2) {
				DrawGraph(areaLeft, recipeY + areaTop - areaY, graphTrailer, true);
			}
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
			break;

		case result:
			break;
		}
		// フリップ（表裏反転）
		ScreenFlip();

		// エラー発生及び閉ウィンドウ or ESCキーでループ解除、DxLib終了へ
		if (ProcessMessage() == -1 || keys[KEY_INPUT_ESCAPE] == 1 && oldkeys[KEY_INPUT_ESCAPE] == 0) { break; }

		// ブレイクポイントを用いたデバッグポーズ
		if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0) {
			WaitTimer(0);	/*<-ここにブレイクポイント*/
		}
	}

	// DxLib終了
	DxLib_End();

	return 0;
}

bool InitializeWindow()
{
	// Log.txtの出力停止
	SetOutApplicationLogValidFlag(FALSE);
	// ウィンドウモード
	ChangeWindowMode(TRUE);
	// ウィンドウサイズ変更不可
	SetWindowSizeChangeEnableFlag(FALSE);
	// ウィンドウタイトル
	SetMainWindowText(TITLE);
	// 解像度、カラービット数設定
	SetGraphMode(WinX, WinY, 32);
	// ゲーム画面対ウィンドウサイズの倍率
	SetWindowSizeExtendRate(1.0);
	// 背景色
	SetBackgroundColor(0, 117, 194);
	// 裏面描画
	SetDrawScreen(DX_SCREEN_BACK);
	// DxLib初期化、エラー発生時には即終了
	if (DxLib_Init() == -1) { return false; }

	return true;
}