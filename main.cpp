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
	// �E�B���h�E�֌W�̊e������
	if (InitializeWindow() == false) { return -1; }

	// �V�[���C���X�^���X
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

	// �Q�[�����ϐ�
	srand(int(time(NULL)));

	// ���\�[�X�n�ϐ�
	int bgm01 = LoadSoundMem("Sounds/stage02_a.mp3");	/*��U�̉��u��*/
	int bgm02 = LoadSoundMem("Sounds/stage02_b.mp3");
	int bgm03 = LoadSoundMem("Sounds/stage03.mp3");
	int bgmBoss = LoadSoundMem("Sounds/stageBoss.mp3");
	int bgmMix = LoadSoundMem("Sounds/mixing.mp3");		/*���[�v�J�E���g=5175*/
	int loopTime = 0;
	int soundWarp = LoadSoundMem("Sounds/warp.mp3");
	int soundShot = LoadSoundMem("Sounds/shot.mp3");

	// �L�[�{�[�h���͏��A�ŐV���O�t���[��
	char keys[256] = {};
	char oldkeys[256] = {};

	// �Q�[�����[�v
	while (1)
	{
		// �S�L�[�{�[�h���͏��X�V
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		GetHitKeyStateAll(keys);

		// ��ʃ��Z�b�g
		ClearDrawScreen();

		/*�Q�[������*/
		/*BGM�Đ�*/
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

		// �V�[���J��
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

		// �t���b�v�i�\�����]�j
		ScreenFlip();

		// �G���[�����y�ѕE�B���h�E or ESC�L�[�Ń��[�v�����ADxLib�I����
		if (ProcessMessage() == -1 || keys[KEY_INPUT_ESCAPE] == 1 && oldkeys[KEY_INPUT_ESCAPE] == 0) { break; }

		// �u���C�N�|�C���g��p�����f�o�b�O�|�[�Y
		if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0) {
			WaitTimer(0);	/*<-�����Ƀu���C�N�|�C���g*/
		}
	}

	// DxLib�I��
	DxLib_End();

	return 0;
}

bool InitializeWindow()
{
	// Log.txt�̏o�͒�~
	SetOutApplicationLogValidFlag(FALSE);
	// �E�B���h�E���[�h
	ChangeWindowMode(TRUE);
	// �E�B���h�E�T�C�Y�ύX�s��
	SetWindowSizeChangeEnableFlag(FALSE);
	// �E�B���h�E�^�C�g��
	SetMainWindowText(TITLE);
	// �𑜓x�A�J���[�r�b�g���ݒ�
	SetGraphMode(WinX, WinY, 32);
	// �Q�[����ʑ΃E�B���h�E�T�C�Y�̔{��
	SetWindowSizeExtendRate(1.0);
	// �w�i�F
	SetBackgroundColor(0, 117, 194);
	// ���ʕ`��
	SetDrawScreen(DX_SCREEN_BACK);
	// DxLib�������A�G���[�������ɂ͑��I��
	if (DxLib_Init() == -1) { return false; }

	return true;
}