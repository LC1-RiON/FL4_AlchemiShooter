#include "Collision.h"
#include <math.h>

bool Collision::HitCheck(float x1, float y1, float r1, float x2, float y2, float r2)
{
	if (powf(x1 - x2, 2.0f) + powf(y1 - y2, 2.0f) <= powf(r1 + r2, 2.0f)) {
		return true;
	}
	return false;
}
