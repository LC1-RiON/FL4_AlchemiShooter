#include "DxLib.h"
#include <time.h>
#include <math.h>
#include "enumeration.h"
#include "EnemyPattern.h"

const char TITLE[] = "�^�C�g��-TITLE";

const int WinX = 1280;

const int WinY = 720;

bool InitializeWindow();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E�֌W�̊e������
	if (InitializeWindow() == false) { return -1; }

	// �Q�[�����ϐ�
	srand(time(NULL));

	// �v���C�G���A_x650:y700
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

	// ���\�[�X�n�ϐ�
	int graphPlayer = LoadGraph("Graphics/player.png");
	int sizePlayerX;
	int sizePlayerY;
	GetGraphSize(graphPlayer, &sizePlayerX, &sizePlayerY);
	int graphEnemy01 = LoadGraph("Graphics/enemy01.png");
	int sizeEnemyX;
	int sizeEnemyY;
	GetGraphSize(graphEnemy01, &sizeEnemyX, &sizeEnemyY);

	int bgm03 = LoadSoundMem("Sounds/stage03.mp3");

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
		// UPDATE
		/*BGM�Đ�*/
		if (CheckSoundMem(bgm03) == 0) { PlaySoundMem(bgm03, DX_PLAYTYPE_BACK); }

		/*���@�ړ�*/
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
		/*�G�ړ�*/
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
		/*�ˌ�*/
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
		/*�ˌ��e*/
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
		/*�Փ˔���*/
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

		/*�o��*/
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