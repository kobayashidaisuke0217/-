#pragma once
#include "struct.h"

class Nucleus{
public:
	Nucleus(Circle nucleus);

public:
	Circle nucleus;

	Vector2 nucleusPrePos;
	Vector2 nucleusSuctionPos;
	int nucleusSuctionCount;
	int max;
	int nucleusCountfrag;

	float exterior;
	float exterior2;
	float exterior3;

	float enemyexterior;
	float enemyexterior2;
	float enemyexterior3;
	int nucleusSuctionFlag;
};

