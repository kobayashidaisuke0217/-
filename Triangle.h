#pragma once
#include "struct.h"

class Triangle {
public:
	Triangle(Line line);


public:
	Line line;
	Line originalLine;

	int PressCount;
	float playerSpeed;
	Vector2 atackSpeed;

	int mouseX, mouseY;
	Vector2 mouse;
	float stop;

	int pattern;

	float playerEndSpeed;
	Vector2 playerAngle;

	float triangleSpeed;

	Vector2 preLineEnd;
	Vector2 preLineVertex;
};
