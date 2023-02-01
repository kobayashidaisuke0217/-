#pragma once
#include "struct.h"

class Player {
public:
	Player(Circle player,Vector2 scroll);
	void Reset();
	void Reflect();
	void Move(char keys[], char preKeys[],int leftx,int lefty,Vector2 scrollStart,Vector2 scrollEnd,int scrollMode);
	void Draw();
	void Hit();
	void Deth();
public:
	Circle player;
	bool hit;
	bool reflect;
	int reflectCount;
	int hitCount;
	int damage;
	int HP;
	Vector2 scroll;
	
};
