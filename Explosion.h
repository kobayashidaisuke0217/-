#pragma once
#include "Vec2.h"

class Explosion {
public:

	Explosion();

	void Update();

	void Draw(Vector2 scroll);

public:
	Vector2 pos;
	int explosionTimer;
	int explosionFlag;
	int explosionCount;
	int enemyAlphaTimer;

	int ex[13];
};