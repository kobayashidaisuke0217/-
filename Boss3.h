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
	int BossRandCount;
	enum choice {
		rotate,
		baria,

	};
	
};
void Boss3Reset(Boss3& boss,Baria &baria);
void BossAtackRotate();
void BossBaria(Boss3& a, Vector2& Atack, float& atackRadius, Baria& baria, bool& AtackFlag, int& atackCoun);
void BossPattern();