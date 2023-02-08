#pragma once
#include "struct.h"
typedef struct Tutrial {
	Vector2 pos;
	float speed;
	Circle player;
	float sizeX;
	float sizeY;
	bool downFlag;
	Vector2 Ob;
	Vector2 moveob;
	int count;
	int moveCount;
};
void TutrialCome(Tutrial& a, Vector2 player);
void TutrialReset(Tutrial& a);
void TutorialMove(Tutrial& a);
void TutorialPowerUp(Tutrial &a, Vector2 scroll, int pic1,int pic2, int pic3);
void TutorialRepel(Tutrial& a, int pic, int pic2, Vector2 scroll);
void TutrialGauge(Tutrial& a,Vector2 &scroll, int pic,  int pic2,int pic3,int pic4, int pic5, int pic6, int pic7 );
void TutrialMoveReset(Tutrial& a, Vector2& scroll, int pic,int pic2);
void TutrialAttack(Tutrial& a, Vector2& scroll, int pic, int pic2, int pic3);