#pragma once

#include "collisionfunc.h"
#include "matrix.h"
typedef struct Baria {
	Vector2 pos;
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftDown;
	Vector2 rightDown;
	Vector2 Endpos;
	float Radius;
	bool isAlive;
	bool Flag;
	int count;
	int alpha;
	int breakCount;
	int HP;
	int size;
};
typedef struct Boss3 {
	Vector2 pos;
	float radius;
	
	int HP;
	int isAlive;
	int patten;
	int BossRandCount;

	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftDown;
	Vector2 rightDown;

	float theta;
	enum choice {
		rotate,
		baria,

	};
	
};
void Boss3Reset(Boss3& boss,Baria &baria);
void BossAtackRotate();
void BossBaria(Boss3& a,  Baria& baria);
void BossPattern();
void BossBariaCollision(Baria& baria, Vector2& atack, float& radius,int& count, bool& flag);