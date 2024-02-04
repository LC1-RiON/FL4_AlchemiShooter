#include "DxLib.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "MixScene.h"
#include "ResultScene.h"
#include "DataManager.h"
#include <time.h>
#include <math.h>
#include "enumeration.h"

#define PI	3.14159265359f
#define DX_DIV_PI_F	(3.14159265359f / 2.0f)

const char TITLE[] = "AlchemiShooter";

const int WinX = 1280;

const int WinY = 720;

bool InitializeWindow();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウ関係の各初期化
	if (InitializeWindow() == false) { return -1; }

	// シーンインスタンス
	int scene = title;
	int nextScene = scene;

	TitleScene* titleScene = new TitleScene(WinX, WinY);
	GameScene* gameScene = new GameScene();
	MixScene* mixScene = new MixScene();
	ResultScene* resultScene = new ResultScene();
	DataManager* dataManager = new DataManager();

	titleScene->Initialize();
	gameScene->FirstInit();
	mixScene->FirstInit();
	resultScene->Initialize();

	// ゲーム内変数
	srand(int(time(NULL)));

	// リソース系変数
	int bgm01 = LoadSoundMem("Sounds/stage02_a.mp3");	/*一旦の仮置き*/
	int bgm02 = LoadSoundMem("Sounds/stage02_b.mp3");
	int bgm03 = LoadSoundMem("Sounds/stage03.mp3");
	int bgmBoss = LoadSoundMem("Sounds/stageBoss.mp3");
	int bgmMix = LoadSoundMem("Sounds/mixing.mp3");		/*ループカウント=5175*/
	int loopTime = 0;
	int soundWarp = LoadSoundMem("Sounds/warp.mp3");
	int soundShot = LoadSoundMem("Sounds/shot.mp3");

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
		/*BGM再生*/
		//if (CheckSoundMem(bgmMix) == 0) { PlaySoundMem(bgmMix, DX_PLAYTYPE_BACK); }
		//if (CheckSoundMem(bgmMix) == 0) { PlaySoundMem(bgmMix, DX_PLAYTYPE_LOOP); }
		//else {
		//	loopTime++;
		//	if (loopTime >= 3863) {
		//		loopTime = 0;
		//		PlaySoundMem(bgmMix, DX_PLAYTYPE_BACK);
		//	}
		//}
		switch (scene)
		{
		case title:
			nextScene = titleScene->Update(keys, oldkeys);

			titleScene->Draw();
			break;

		case play:
			nextScene = gameScene->Update(keys, oldkeys);

			gameScene->Draw();
			break;

		case mix:
			nextScene = mixScene->Update(keys, oldkeys);

			mixScene->Draw();
			break;

		case result:
			nextScene = resultScene->Update();

			resultScene->Draw();
			break;
		}

		// シーン遷移
		if (scene != nextScene) {
			switch (nextScene)
			{
			case title:
				titleScene->Initialize();
				break;

			case play:
				if (scene == mix) {
					mixScene->DataSave(dataManager);
					gameScene->Initialize(dataManager);
				}
				else {
					gameScene->FirstInit();
				}
				break;

			case mix:
				if (scene == play) {
					gameScene->DataSave(dataManager);
					mixScene->Initialize(dataManager);
				}
				break;

			case result:
				resultScene->Initialize();
				break;
			}
			scene = nextScene;
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