#pragma once
#include "struct.h"
#include "Vec2.h"
#include "matrix.h"
typedef struct particle {
	Vector2 pos;
	int count;
	bool isAlive;
	Vector2 start;
	Vector2 End;
	Vector2 vertex;
	Vector2 originalstart;
	Vector2 originalEnd;
	Vector2 originalvertex;
	float theta;
	float randStart;
};
typedef struct parManag {
	particle par[16];
};
void particleTriangle(parManag& par, Vector2 player);