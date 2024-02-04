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
	float x[TOTALWAVE][WAVELIMIT] = {};
	float y[TOTALWAVE][WAVELIMIT] = {};
	float moveAngle[TOTALWAVE][WAVELIMIT] = {};
	float moveSpeed[TOTALWAVE][WAVELIMIT] = {};
	int count = 0;
	int wave = 0;

public:
	EnemyPattern();

	~EnemyPattern();

	void Setting(int setWave);

	int SpawnCheck(int timer);

	void Spawn(int* enemyType, int* enemyHP, float* enemyX, float* enemyY, float* enemyMoveAngle, float* enemyMoveSpeed);
};
