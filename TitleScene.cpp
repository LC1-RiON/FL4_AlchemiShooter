#include "TitleScene.h"
#include "enumeration.h"

TitleScene::TitleScene(int WinX, int WinY)
{
	titleFlash = 0;
	pushed = false;

	LoadDivGraph("Graphics/title.png", 4, 4, 1, WinX, WinY, graphTitle);
	soundEnter = LoadSoundMem("Sounds/Enter.mp3");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	titleFlash = 0;
}

int TitleScene::Update(char* keys, char* oldkeys)
{
	titleFlash++;
	if (titleFlash >= flashRate * 4) { titleFlash -= (flashRate * 4); }
	if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0 && pushed == false) {
		pushed = true;
		PlaySoundMem(soundEnter, DX_PLAYTYPE_BACK);
	}
	if (pushed == true && CheckSoundMem(soundEnter) == 0) {
		return play;
	}

	return title;
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, graphTitle[titleFlash / flashRate], true);
}
