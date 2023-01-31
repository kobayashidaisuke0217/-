#pragma once
#include "struct.h"

class Player {
public:
	Player(Circle player,Vector2 scroll);
	
	void Move(char keys[], char preKeys[],int leftx,int lefty,Vector2 scrollStart,Vector2 scrollEnd,int scrollMode);
	void Draw();
	void Hit();
public:
	Circle player;
	bool hit;
	int hitCount;
	Vector2 scroll;
	
};
