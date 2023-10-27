#include "DxLib.h"
#include <time.h>
#include <math.h>
#include "enumeration.h"
#include "EnemyPattern.h"

const char TITLE[] = "タイトル-TITLE";

const int WinX = 1280;

const int WinY = 720;

bool InitializeWindow();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウ関係の各初期化
	if (InitializeWindow() == false) { return -1; }

	// ゲーム内変数
	srand(time(NULL));

	// プレイエリア_x650:y700
	int areaLeft = 100;
	int areaTop = 10;
	int areaX = 650;
	int areaY = 700;

	int x = areaX / 2;
	int y = areaY - 100;
	int r = 20;

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
	pattern->Setting(1);
	int playTimer = 0;

	int material[3] = {};

	const int ALLBEAM = 500;
	float beamX[ALLBEAM];
	float beamY[ALLBEAM];
	int beamR = 5;
	float beamMoveX[ALLBEAM];
	float beamMoveY[ALLBEAM];
	bool shot[ALLBEAM];
	int beamType[ALLBEAM];
	int forHoming[ALLBEAM];
	int homingLocked = ENEMYLIMIT * 10;
	for (int i = 0; i < ALLBEAM; i++) {
		shot[i] = false;
	}
	int shotNum = 0;
	int reload = 0;

	// リソース系変数
	int graphPlayer = LoadGraph("Graphics/player.png");
	int sizePlayerX;
	int sizePlayerY;
	GetGraphSize(graphPlayer, &sizePlayerX, &sizePlayerY);
	int graphEnemy01 = LoadGraph("Graphics/enemy01.png");
	int sizeEnemyX;
	int sizeEnemyY;
	GetGraphSize(graphEnemy01, &sizeEnemyX, &sizeEnemyY);

	int bgm03 = LoadSoundMem("Sounds/stage03.mp3");

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
		if (CheckSoundMem(bgm03) == 0) { PlaySoundMem(bgm03, DX_PLAYTYPE_BACK); }

		/*自機移動*/
		if (keys[KEY_INPUT_RIGHT] == 1) {
			x += 4;
			if (x > areaX) { x = areaX; }
		}
		if (keys[KEY_INPUT_LEFT] == 1) {
			x -= 4;
			if (x < 0) { x = 0; }
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
				}
			}
		}
		/*射撃*/
		if (reload > 0) { reload--; }
		if (keys[KEY_INPUT_SPACE] == 1 && reload <= 0) {
			while (shot[shotNum] == true) { shotNum++; }
			/* NormalShot */
			beamX[shotNum] = x;
			beamY[shotNum] = y;
			beamMoveY[shotNum] = -10;
			shot[shotNum] = true;
			beamType[shotNum++] = normal;
			if (shotNum >= ALLBEAM) { shotNum = 0; }
			reload = 3;

			/* TwinShot */
			//for (int i = 1; i > -2; i -= 2) {
			//	beamX[shotNum] = x;
			//	beamY[shotNum] = y;
			//	beamMoveX[shotNum] = 2 * i;
			//	beamMoveY[shotNum] = -10;
			//	shot[shotNum] = true;
			//	if (i > 0) { beamType[shotNum++] = right; }
			//	else { beamType[shotNum++] = left; }
			//	if (shotNum >= _countof(shot)) { shotNum = 0; }
			//}
			//reload = 3;

			/* HomingShot */
			//beamX[shotNum] = x;
			//beamY[shotNum] = y;
			//beamMoveX[shotNum] = 0;
			//beamMoveY[shotNum] = 1;
			//shot[shotNum] = true;
			//beamType[shotNum] = homing;
			//forHoming[shotNum] = 0;
			//shotNum++;
			//if (shotNum >= _countof(shot)) { shotNum = 0; }
			//reload = 20;
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
					beamX[i] += beamMoveX[i];
					beamY[i] += beamMoveY[i];
					break;

				case left:
					beamX[i] += beamMoveX[i];
					beamY[i] += beamMoveY[i];
					break;

				case homing:
					beamX[i] += beamMoveX[i];
					beamY[i] += beamMoveY[i];
					if (forHoming[i] < 100) { forHoming[i]++; }
					else {
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
		for (int i = 0; i < ALLBEAM; i++)
		{
			for (int j = 0; j < ENEMYLIMIT; j++)
			{
				if (shot[i] == true && enemyAlive[j] == true &&
					pow(beamX[i] - enemyX[j], 2.0) + pow(beamY[i] - enemyY[j], 2.0) <= pow(beamR + enemyR, 2.0)) {
					shot[i] = false;
					enemyHP[j]--;
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
		}

		/*経過*/
		playTimer++;
		while (pattern->SpawnCheck(playTimer) == true)
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

		// DRAW
		DrawGraph(x - sizePlayerX / 2 + areaLeft, y - sizePlayerY / 2 + areaTop, graphPlayer, true);
		DrawCircle(x + areaLeft, y + areaTop, r, GetColor(128, 128, 255), FALSE);
		for (int i = 0; i < ENEMYLIMIT; i++)
		{
			if (enemyAlive[i] == true) {
				DrawCircle(enemyX[i] + areaLeft, enemyY[i] + areaTop, enemyR, GetColor(77, 255, 77));
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
				DrawString(i % 100 * 6 + i / 100, i / 100 * 10, "|", GetColor(255, 255, 255));
			}
			else {
				DrawString(i % 100 * 6 + i / 100, i / 100 * 10, "|", GetColor(0, 0, 0));
			}
		}
		DrawBox(areaLeft, areaTop, areaLeft + areaX, areaTop + areaY, GetColor(128, 255, 128), FALSE);
		DrawFormatString(0, 700, GetColor(255, 255, 255), "%dx%d_LeftTop:%d", areaX, areaY, areaLeft);
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