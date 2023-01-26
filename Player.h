#pragma once
#include "struct.h"

class Player {
public:
	Player(Circle player,Vector2 scroll);
	
	void Move(char keys[], char preKeys[],int leftx,int lefty,Vector2 scrollStart,Vector2 scrollEnd,int scrollMode);
	void Draw();

public:
	Circle player;

	Vector2 scroll;
	
};
