#include "Boss3.h"
void Boss3Reset(Boss3& boss, Baria& baria,BossBeam &beam) {
	boss.patten = 0;

	boss.pos = { 1280,720 };
	boss.leftDown = { 0,0 };
	boss.leftTop = { 0,0 };
	boss.rightDown = { 0,0 };
	boss.rightTop = { 0,0 };
	boss.radius = 128;
	boss.HP = 100;
	boss.isAlive = true;



	baria.alpha = 0;
	baria.breakCount = 0;
	baria.count = 0;
	baria.Flag = false;
	baria.HP = 0;
	baria.pos = { 0,0 };
	baria.leftDown = { 0,0 };
	baria.leftTop = { 0,0 };
	baria.rightDown = { 0,0 };
	baria.rightTop = { 0,0 };
	
	baria.Endpos = {0,0};
	baria.size = 20;
	baria.isAlive = false;

	beam.count = 0;
	beam.EndPos = { 0,0 };
	beam.flag = false;
	beam.leftDown = { 0,0 };
	beam.leftTop={ 0,0 };
	beam.ob = { 0,0 };
	beam.pos = { 0,0 };
	beam.rightDown = { 0,0 };
	beam.rightTop = { 0,0 };
	beam.theta = 0;
	beam.size = 16;
}
void BossAtackRotatet(Boss3 &a) {

}
void BossBariaCollision(Baria& baria, Vector2& atack, float& radius, int& count, bool& flag) {
	if (flag== true&&count<3) {
		if (RectCollisionHit(baria.pos, baria.Endpos, atack, radius, baria.size) == true) {
			flag = false;
			baria.HP -= 1;
			baria.alpha = 255;
		
		}
	}
}

void BossBaria(Boss3& boss, Baria& baria ) {
	if (baria.isAlive == true) {
		baria.count++;
		if (baria.alpha > 0) {
			baria.alpha -= 10;
		}
		if (baria.alpha < 30) {
			baria.alpha = 30;
		}
		/*	if (AtackFlag == true) {
				if (RectCollisionHit(baria.pos,baria.Endpos,Atack, atackRadius, baria.size) == true) {
					AtackFlag = false;
					baria.HP -= 1;
					baria.alpha = 255;
				}
			}*/
		if (baria.HP <= 0) {
			baria.isAlive = false;
		}

		if (baria.count >= 480) {
			baria.count = 0;
		}
		Vector2 bariaAngle = { baria.pos.x - baria.Endpos.x,baria.pos.y - baria.Endpos.y };
		Vector2 bariaRadian = Normalais(bariaAngle);

		Vector2 topRadian = { -bariaRadian.y,bariaRadian.x };
		Vector2 topAngle = Multiply(topRadian, baria.size);
		baria.leftTop = { baria.pos.x + topAngle.x,baria.pos.y + topAngle.y };
		baria.rightTop = { baria.Endpos.x + topAngle.x,baria.Endpos.y + topAngle.y };

		Vector2 downRadian = { bariaRadian.y,-bariaRadian.x };
		Vector2 downAngle = Multiply(downRadian, baria.size);
		baria.leftDown = { baria.pos.x + downAngle.x,baria.pos.y + downAngle.y };
		baria.rightDown = { baria.Endpos.x + downAngle.x,baria.Endpos.y + downAngle.y };


		if (baria.count <= 120) {
			baria.pos.x = boss.pos.x + 150;
			baria.pos.y = boss.pos.y - 150;
			baria.Endpos.x = boss.pos.x + 150;
			baria.Endpos.y = boss.pos.y + 150;
		}
		else if (baria.count <= 240) {
			baria.pos.x = boss.pos.x - 150;
			baria.pos.y = boss.pos.y - 150;
			baria.Endpos.x = boss.pos.x - 150;
			baria.Endpos.y = boss.pos.y + 150;
		}
		else if (baria.count <= 360) {
			baria.pos.x = boss.pos.x - 150;
			baria.pos.y = boss.pos.y - 150;
			baria.Endpos.x = boss.pos.x + 150;
			baria.Endpos.y = boss.pos.y - 150;
		}
		else if (baria.count <= 480) {
			baria.pos.x = boss.pos.x - 150;
			baria.pos.y = boss.pos.y + 150;
			baria.Endpos.x = boss.pos.x + 150;
			baria.Endpos.y = boss.pos.y + 150;
		}
	}
	if (baria.isAlive == false) {
		baria.breakCount++;
	}
	if (baria.breakCount >= 50) {
		baria.breakCount = 0;
		baria.HP = 5;
		baria.isAlive = true;
		baria.alpha = 255;
	}
}

void BossPattern(Boss3& a) {
	
}
void BossBeamAtack(Boss3& boss, BossBeam& beam, Vector2& player) {
	beam.count++;
	if (beam.count >= 120) {
		beam.flag = true;
	}
	if (beam.flag == true) {
		beam.pos.x = boss.pos.x;
		beam.pos.y = boss.pos.y - boss.radius;

		//if (player.x >= 1280) {
			beam.theta -= 1.0f / 120.0f;
		//}
		/*else {
			beam.theta += 1.0f / 120.0f;
		}*/
		beam.ob = { beam.pos.x + cosf(beam.theta) * 40,beam.pos.y + sinf(beam.theta) * 40 };
		Vector2 beamangle = { beam.ob.x - beam.pos.x,beam.ob.y - beam.pos.y };
		Vector2 beamradian = Normalais(beamangle);
		beam.EndPos = Multiply(beamradian, 2000);
		beam.EndPos.x += beam.pos.x;
		beam.EndPos.y += beam.pos.y;

		Vector2 beamTopAngle = { -beamradian.y,beamradian.x };
		Vector2 beamTopRadian = Multiply(beamTopAngle, beam.size);
		beam.leftTop = { beam.pos.x + beamTopRadian.x,beam.pos.y + beamTopRadian.y };
		beam.rightTop.x = beam.EndPos.x + beamTopRadian.x;
		beam.rightTop.y = beam.EndPos.y + beamTopRadian.y;

		Vector2 beamDownAngle = { beamradian.y,-beamradian.x };
		Vector2 beamDownRadian = Multiply(beamDownAngle, beam.size);
		beam.leftDown = { beam.pos.x + beamDownRadian.x,beam.pos.y + beamDownRadian.y };
		beam.rightDown.x = beam.EndPos.x + beamDownRadian.x;
		beam.rightDown.y = beam.EndPos.y + beamDownRadian.y;
	}
}