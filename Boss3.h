#pragma once

#include "collisionfunc.h"
#include "matrix.h"

typedef struct Baria {
	Vector2 pos;
	int HP;
	bool isAlive;
	int openCount;
	int hitCount;
	float size;
	bool hitFlag;
};
typedef struct Boss3 {
	Vector2 Pos;
	Vector2 radius;

	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftDown;
	Vector2 rightDown;
	Baria gard;
};


void BossAtackRotate(Boss3& a, Vector2& player);

void BossBariaOpen(Baria& a, Vector2& bullet, int count, bool frag);