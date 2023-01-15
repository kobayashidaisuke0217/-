#pragma once

#include "collisionfunc.h"

typedef struct Boss3 {
	Vector2 Pos;
	Vector2 radius;

	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftDown;
	Vector2 rightDown;

	
};
typedef struct Baria {
	Vector2 pos;
	Vector2 HP;
};
void BossAtackRotate();

void BossAtackBeem();