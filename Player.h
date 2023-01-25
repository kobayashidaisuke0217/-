#pragma once
#include "struct.h"

class Player {
public:
	Player(Circle player);
	
	void Move(char keys[], char preKeys[],int leftx,int lefty,Vector2 scrollStart,Vector2 scrollEnd,Vector2 scroll,int scrollMode);
	void Draw();

public:
	Circle player;
	
};
