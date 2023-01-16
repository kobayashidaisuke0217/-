#pragma once

#include "collisionfunc.h"

typedef struct Baria {
	Vector2 pos;
	bool isAlive;
	bool Flag;
};
typedef struct Boss3 {
	Vector2 Pos;
	Vector2 radius;
	Vector2 Beem;
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftDown;
	Vector2 rightDown;
	Baria baria;
	
};

void BossAtackRotate();
void BossBaria();