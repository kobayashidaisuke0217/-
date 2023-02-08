#pragma once
#include "struct.h"
#include "Vec2.h"
#include "matrix.h"
typedef struct particle {
	Vector2 pos;
	int count;
	bool isAlive;
	Vector2 start;
	Vector2 goal;
};
typedef struct parManag {
	particle par[12];
	int count;
	bool isAlive;
	Vector2 ob;
	float theta;
};