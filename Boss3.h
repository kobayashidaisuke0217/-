#pragma once

#include "collisionfunc.h"
#include "matrix.h"
typedef struct Baria {
	Vector2 pos;
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftDown;
	Vector2 rightDown;
	float Radius;
	bool isAlive;
	bool Flag;
	int count;
	int alpha;
	int breakCount;
	int HP;
};
typedef struct Boss3 {
	Vector2 Pos;
	float radius;
	
	int HP;
	int isAlive;
	int patten;
	enum choice {
		rotate,
		baria,

	};
	
};
void Boss3Rest();
void BossAtackRotate();
void BossBaria();
void BossPattern();