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
};

