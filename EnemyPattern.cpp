#include "EnemyPattern.h"
#include <stdlib.h>

EnemyPattern::EnemyPattern()
{
	// 敵出現時データ
	int typeSet[TOTALWAVE][WAVELIMIT] = {
		{
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		},
		{
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	beast,	slime,	slime,	slime,	slime,	beast,	slime,	slime,	slime,
slime,	beast,	beast,	beast,	beast,	beast,	beast,	beast,	beast,	beast,
beast,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		},
		{
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		},
		{
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		},
		{
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,	slime,
		}
	};

	int spawnSet[TOTALWAVE][WAVELIMIT] = {
		{
60,80,100,120,140,200,220,240,260,280,
340,360,380,400,420,520,530,540,550,560,
570,580,590,600,610,800,800,800,800,800,
1000,1000,1000,1000,1000,1400,1400,1400,1400,1400,
1600,1600,1600,1600,1600,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
60,80,100,120,120,140,160,180,180,200,
220,240,400,400,400,460,460,460,520,520,
520,640,670,700,730,760,910,940,970,1000,
1030,1180,1210,1210,1210,1240,1420,1450,1450,1480,
1480,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
		30,50,70,90,110,130,150,170,190,210,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
		30,50,70,90,110,130,150,170,190,210,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
		30,50,70,90,110,130,150,170,190,210,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
		9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		}
	};
	float xSet[TOTALWAVE][WAVELIMIT] = {
		{
325,325,325,325,325,200,200,200,200,200,
450,450,450,450,450,660,-10,660,-10,660,
-10,660,-10,660,-10,-10,-10,-10,-10,-10,
660,660,660,660,660,180,140,100,60,20,
470,510,550,590,630,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
660,660,660,660,-10,-10,-10,-10,660,660,
660,660,540,580,620,110,70,30,285,325,
365,550,550,550,550,550,100,100,100,100,
100,400,340,400,460,400,250,230,270,210,
290,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
		200,	200,	200,	200,	200,	200,	200,	200,	200,	200,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		},
		{
		200,	200,	200,	200,	200,	200,	200,	200,	200,	200,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		},
		{
		200,	200,	200,	200,	200,	200,	200,	200,	200,	200,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		}
	};
	float ySet[TOTALWAVE][WAVELIMIT] = {
		{
-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,
-10,-10,-10,-10,-10,100,100,100,100,100,
100,100,100,100,100,260,220,180,140,100,
240,200,160,120,80,-10,-10,-10,-10,-10,
-10,-10,-10,-10,-10,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
100,100,100,100,160,160,160,160,220,220,
220,220,-10,-10,-10,-10,-10,-10,-10,-10,
-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,
-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,
-10,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
		-10,	-10,	-10,	-10,	-10,	-10,	-10,	-10,	-10,	-10,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		},
		{
		-10,	-10,	-10,	-10,	-10,	-10,	-10,	-10,	-10,	-10,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		},
		{
		-10,	-10,	-10,	-10,	-10,	-10,	-10,	-10,	-10,	-10,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		}
	};
	float moveAngleSet[TOTALWAVE][WAVELIMIT] = {
		{
90,90,90,90,90,90,90,90,90,90,
90,90,90,90,90,135,45,135,45,135,
45,135,45,135,45,0,0,0,0,0,
180,180,180,180,180,90,90,90,90,90,
90,90,90,90,90,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
180,180,180,180,0,0,0,0,180,180,
180,180,135,135,135,45,45,45,90,90,
90,90,90,90,90,90,90,90,90,90,
90,90,90,90,90,90,90,90,90,90,
90,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		},
		{
		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		},
		{
		0,		0,		0,		0,		0,		0,		0,		0,		0,		0,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		}
	};
	float moveSpeedSet[TOTALWAVE][WAVELIMIT] = {
		{
2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
2,2,2,2,2,2,2,2,2,2,
2,2,3,3,3,3,3,3,3,3,
3,2,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,
2,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999,
9999,9999,9999,9999,9999,9999,9999,9999,9999,9999
		},
		{
		2,		2,		2,		2,		2,		2,		2,		2,		2,		2,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		},
		{
		2,		2,		2,		2,		2,		2,		2,		2,		2,		2,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		},
		{
		2,		2,		2,		2,		2,		2,		2,		2,		2,		2,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,
		9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999,	9999
		}
	};
	for (int i = 0; i < TOTALWAVE; i++)
	{
		for (int j = 0; j < WAVELIMIT; j++)
		{
			type[i][j] = typeSet[i][j];
			spawn[i][j] = spawnSet[i][j];
			x[i][j] = xSet[i][j];
			y[i][j] = ySet[i][j];
			moveAngle[i][j] = moveAngleSet[i][j];
			moveSpeed[i][j] = moveSpeedSet[i][j];
			switch (type[i][j])
			{
			case slime:
				hp[i][j] = 30;
				break;
			case beast:
				hp[i][j] = 80;
				break;
			case fairy:
				hp[i][j] = 40;
				break;
			}
		}
	}
	count = 0;
	wave = 0;
}

EnemyPattern::~EnemyPattern()
{
}

void EnemyPattern::Setting(int setWave)
{
	wave = setWave - 1;
	count = 0;
}

int EnemyPattern::SpawnCheck(int timer)
{
	if (timer >= spawn[wave][count]) { return 1; }
	else if (spawn[wave][count] == 9999) { return 9999; }
	return 0;
}

void EnemyPattern::Spawn(int* enemyType, int* enemyHP, float* enemyX, float* enemyY, float* enemyMoveAngle, float* enemyMoveSpeed)
{
	*enemyType = type[wave][count];
	*enemyHP = hp[wave][count];
	*enemyX = x[wave][count];
	*enemyY = y[wave][count];
	*enemyMoveAngle = moveAngle[wave][count];
	*enemyMoveSpeed = moveSpeed[wave][count++];
}
