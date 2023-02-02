#include "tutorial.h"
#include "Boss3.h"
#include"Novice.h"
//float learp(float t, float s, float e) {
//	return (1.0f - t) * s + t * e;
//}
void TutrialCome(Tutrial& a, Vector2 player) {
	float length = a.pos.x - player.x;
	if (length <= 50 && length >= -50) {
		a.downFlag = true;
		
	}
	if (a.downFlag == true) {
		if (a.speed <= 1.0f) {
			a.speed += 1.0f / 30.0f;
		}
		a.pos.y = learp(a.speed, -400, 200);
		a.player.center.y = learp(a.speed, -300, 300);
		a.Ob.y = learp(a.speed, -300, 300);
		a.moveob = a.Ob;
	}
}
void TutrialReset(Tutrial& a) {
	a.player = { a.pos.x + 10,a.pos.y + 100,16,0,WHITE,1 };
	a.pos = { a.pos.x,-400 };
	a.sizeX = 300;
	a.sizeY = 200;
	a.speed = 0;
	a.downFlag = false;
	a.Ob = { a.pos.x + 32,a.pos.y + 100 };
	a.moveob = a.Ob;
	a.count = 0;
	a.moveCount = 0;
}
void TutorialMove(Tutrial& a) {
	a.count++;
	if (a.count <= 20) {
		a.Ob.x = a.moveob.x + 10;
		a.Ob.y = a.moveob.y;
		a.player.center.x += 2;
		a.player.center.y = a.Ob.y;
	}
	else if (a.count <= 40) {
		a.Ob.x = a.moveob.x;
		//a.Ob.y = a.moveob.y + 10;
		a.player.center.x = a.pos.x+100;
		//a.player.center.y +=2 ;
	}
	else if (a.count <= 60) {
		a.Ob.x = a.moveob.x-10;
		a.Ob.y = a.moveob.y ;
		a.player.center.x -= 2;
		a.player.center.y = a.Ob.y;
	}
	else {
		a.Ob.x = a.moveob.x;
		//a.Ob.y = a.moveob.y - 10;
		a.player.center.x = a.pos.x + 100;
		//a.player.center.y -= 2;
	}
	if (a.count >= 80) {
		a.count = 0;
	}
}
void TutorialRepel(Tutrial& a, int pic, int pic2,Vector2 scroll) {
	if (a.moveCount == 0) {
		if (a.player.speed <= 1.0f) {
			a.player.speed += 1.0f / 30.0f;
		}
		else {
			a.moveCount = 1;
			a.player.speed = 0;
		}
		a.player.center = { learp(a.player.speed,a.pos.x + 40,a.pos.x + 150),learp(a.player.speed,a.pos.y + 100,a.pos.y + 50) };
		Novice::DrawLine(a.pos.x + 40-scroll.x, a.pos.y + 100 - scroll.y, a.player.center.x - scroll.x, a.player.center.y - scroll.y, WHITE);
	}
	if (a.moveCount == 1) {
		if (a.player.speed <= 1.0f) {
			a.player.speed += 1.0f / 30.0f;
		}
		else {
			a.moveCount = 2;
			a.player.speed = 0;
		}
		a.player.center = { learp(a.player.speed,a.pos.x + 150,a.pos.x + 150),learp(a.player.speed,a.pos.y + 50,a.pos.y + 150) };
		Novice::DrawLine(a.pos.x + 150 - scroll.x, a.pos.y + 50 - scroll.y, a.player.center.x - scroll.x, a.player.center.y - scroll.y, WHITE);
	}
	if (a.moveCount == 2) {
		if (a.player.speed <= 1.0f) {
			a.player.speed += 1.0f / 30.0f;
		}
		else {
			a.count ++;
			
		}
		if (a.count >= 50) {
			a.moveCount = 0;
			a.count = 0;
			a.player.speed = 0;
		}
		a.player.center = { learp(a.player.speed,a.pos.x + 150,a.pos.x + 40),learp(a.player.speed,a.pos.y +150,a.pos.y + 100) };
		Novice::DrawLine(a.pos.x + 150 - scroll.x, a.pos.y + 150 - scroll.y, a.player.center.x - scroll.x, a.player.center.y - scroll.y, WHITE);
	}
	if (a.moveCount > 0) {
		Novice::DrawLine(a.pos.x + 40 - scroll.x, a.pos.y + 100 - scroll.y, a.pos.x+150 - scroll.x, a.pos.y+50 - scroll.y, WHITE);

	}
	if (a.moveCount > 1) {
		Novice::DrawLine(a.pos.x + 150 - scroll.x, a.pos.y + 50 - scroll.y, a.pos.x+150 - scroll.x, a.pos.y+150 - scroll.y, WHITE);

	}
	/*if (a.moveCount > 2) {
		Novice::DrawLine(a.pos.x + 150 - scroll.x, a.pos.y + 50 - scroll.y, a.pos.x + 150 - scroll.x, a.pos.y + 150 - scroll.y, WHITE);

	}*/
	a.Ob = { a.pos.x + 100,a.pos.y + 100 };
	Novice::DrawSprite(a.player.center.x - scroll.x-16, a.player.center.y - scroll.y-16, pic, 0.5, 0.5, 0, WHITE);
	Novice::DrawSprite(a.Ob.x - scroll.x, a.Ob.y - scroll.y, pic2, 0.5, 0.5, 0, WHITE);

}
 void TutrialGauge(Tutrial& a,Vector2 &scroll, int pic,int pic2,int pic3) {
	 if (a.count <= 100) {
		 a.count++;
	 }
	 else {
		 a.count = 0;
	 }
	 a.Ob = { a.pos.x + 100,a.pos.y + 20 };
	 a.moveob = { a.pos.x + 200,a.pos.y + 120 };
	 Novice::DrawBox(a.player.center.x - scroll.x, a.pos.y - scroll.y+35, a.count * 2, 16, 0, WHITE, kFillModeSolid);
	 Novice::DrawSprite(a.Ob.x - scroll.x, a.Ob.y - scroll.y, pic, 2, 2, 0, WHITE);

	 Novice::DrawSprite(a.moveob.x - scroll.x, a.moveob.y - scroll.y, pic2, 2, 2, 0, WHITE);
	 Novice::DrawSprite(a.moveob.x - scroll.x+70, a.moveob.y - scroll.y, pic3, 2, 2, 0, WHITE);
	 Novice::DrawBox(a.moveob.x - scroll.x + 30, a.moveob.y - scroll.y, 35, 10, 0, WHITE, kFillModeSolid);
	 Novice::DrawBox(a.moveob.x - scroll.x + 43, a.moveob.y - scroll.y-10, 10, 35, 0, WHITE, kFillModeSolid);
}
 void TutrialMoveReset(Tutrial& a,Vector2 &scroll, int pic) {
	 a.Ob = { a.pos.x + 100,a.pos.y + 20 };
	 
	 Novice::DrawSprite(a.Ob.x - scroll.x, a.Ob.y - scroll.y, pic, 2, 2, 0, WHITE);
}
 void TutrialAttack(Tutrial& a, Vector2& scroll, int pic, int pic2, int pic3) {
	 a.Ob = { a.pos.x + 20,a.pos.y + 100 };
	 a.moveob = { a.pos.x + 200,a.pos.y + 120 };
	 Novice::DrawSprite(a.Ob.x - scroll.x, a.Ob.y - scroll.y, pic, 0.5, 0.5, 0, WHITE);
	 Novice::DrawTriangle(a.Ob.x+50 - scroll.x, a.Ob.y  - scroll.y, a.Ob.x + 100 - scroll.x, a.Ob.y  - scroll.y, a.Ob.x + 100 - scroll.x, a.Ob.y + 50 - scroll.y,WHITE,kFillModeWireFrame);

	 Novice::DrawSprite(a.moveob.x - scroll.x, a.moveob.y - scroll.y, pic2, 2, 2, 0, WHITE);
	 Novice::DrawSprite(a.moveob.x - scroll.x + 70, a.moveob.y - scroll.y, pic3, 2, 2, 0, WHITE);
	 Novice::DrawBox(a.moveob.x - scroll.x + 30, a.moveob.y - scroll.y, 35, 10, 0, WHITE, kFillModeSolid);
	 Novice::DrawBox(a.moveob.x - scroll.x + 43, a.moveob.y - scroll.y - 10, 10, 35, 0, WHITE, kFillModeSolid);
 }
