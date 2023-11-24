#pragma once
#include "enumeration.h"

const int TOTALWAVE = 5;
const int WAVELIMIT = 100;

class EnemyPattern
{
private:
	int type[TOTALWAVE][WAVELIMIT] = {};
	int hp[TOTALWAVE][WAVELIMIT] = {};
	int spawn[TOTALWAVE][WAVELIMIT] = {};
	int x[TOTALWAVE][WAVELIMIT] = {};
	int y[TOTALWAVE][WAVELIMIT] = {};
	int moveX[TOTALWAVE][WAVELIMIT] = {};
	int moveY[TOTALWAVE][WAVELIMIT] = {};
	int count = 0;
	int wave = 0;

public:
	EnemyPattern();

	~EnemyPattern();

	void Setting(int setWave);

	int SpawnCheck(int timer);

	void Spawn(int* enemyType, int* enemyHP, int* enemyX, int* enemyY, int* enemyMoveX, int* enemyMoveY);
};
