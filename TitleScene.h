#pragma once
#include "DxLib.h"
class TitleScene
{
private:
	int titleFlash = 0;
	const int flashRate = 40;

	int graphTitle[4];

public:
	TitleScene(int WinX, int WinY);

	~TitleScene();

	void Initialize();

	int Update(char* keys, char* oldkeys);

	void Draw();
};

