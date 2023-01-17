#include "Boss3.h"
void Boss3reset(Boss3& boss, Baria& baria) {
	boss.patten = 0;
	boss.leftDown = { 0, 0};
	boss.leftTop = { 0,0 };
	boss.rightDown = { 0,0 };
	boss.rightTop = { 0,0 };
	boss.Pos = { 1280,720 };
	boss.radius = 128;
	boss.HP = 100;
	boss.isAlive = true;
	baria.alpha = 0;
}
void BossAtackRotatet(Boss3 &a, Vector2 &player) {

}


void BossBaria(Boss3& a,Vector2 &Atack,float &atackRadius ,Baria &baria,bool &AtackFlag) {
	if (baria.isAlive == true) {
		baria.count++;
		if (baria.alpha > 0) {
			baria.alpha-=10;
		}
		if (baria.alpha < 0) {
			baria.alpha = 0;
		}
		if (AtackFlag == true) {
			if (CircleCollisinHit(baria.pos, baria.Radius, Atack, atackRadius) == true) {
				AtackFlag = false;
				baria.HP -= 1;
				baria.alpha = 255;
		}
		}
		if (baria.HP <= 0) {
			baria.isAlive = false;
		}
   }
	if (baria.count >= 240) {
		baria.count = 0;
	}
	if (baria.isAlive == false) {
		baria.breakCount++;
	}
	if (baria.breakCount >= 500) {
		baria.breakCount = 0;
		baria.isAlive = true;
	}
}

void BossPattern(Boss3& a) {
	
}