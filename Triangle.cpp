#include "Triangle.h"

Triangle::Triangle(Line line) {
	line = {
		{1000.0f,700.0f},
		{500.0f,400.0f},
		{100,500},
	};
	originalLine = {
		{24.0f,24.0f},
		{0.0f,-36.0f},
		{-24.0f,24.0f},
	};

	PressCount = 0;
	playerSpeed = 0;
	atackSpeed = { 0 };

	mouseX, mouseY = 0;
	mouse = { 0 };
	stop = 0.93;

	pattern = 0;

	playerEndSpeed;
	playerAngle = { 0 };

	triangleSpeed = 0;

	preLineEnd = { 0 };
	preLineVertex = { 0 };
}