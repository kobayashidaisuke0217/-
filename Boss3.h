#pragma once

#include "collision.h"

typedef struct Boss3 {
	Vector2 Pos;
	Vector2 radius;
	Vector2 Beem;
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftDown;
	Vector2 rightDown;

	
};
void BossAtackRotate();