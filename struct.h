#pragma once
#include "Vec2.h"
struct Circle {
	Vector2 center;//’†S
	float radius;//”¼Œa
	float speed;//‘¬“x
	unsigned int color;
	int HP;
};

struct Bullet {
	Vector2 center;
	float radius;
	Vector2 speed;
	unsigned int color;
};

struct Line {
	Vector2 start;
	Vector2 vertex;
	Vector2 end;
};

