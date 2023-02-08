#pragma once
#include "struct.h"

class FireWorks {
public:
	FireWorks();

	void Update(char keys[]);

	void Draw(int color);

public:
	Bullet fireWorksCenter;
	Bullet fireWorks[64];

	int fireWorksAlpha;
	int fireTimer;
	int fireFlag;
	int startFlag;
};
