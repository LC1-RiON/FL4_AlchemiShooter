#include "TitleScene.h"
#include "enumeration.h"

TitleScene::TitleScene(int WinX, int WinY)
{
	titleFlash = 0;

	LoadDivGraph("Graphics/title.png", 4, 4, 1, WinX, WinY, graphTitle);
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
	for (int i = 0; i < 256; i++)
	{
		if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0) {
			return play;
		}
	}

	return title;
}

void TitleScene::Draw()
{
	DrawGraph(0, 0, graphTitle[titleFlash / flashRate], true);
}
