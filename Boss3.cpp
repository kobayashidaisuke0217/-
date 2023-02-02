#include "Boss3.h"
float learp(float t, float s, float e) {
	return (1.0f - t) * s + t * e;
}
void Boss3Reset(Boss3& boss, Baria& baria, BossBeam& beam) {
	boss.patten = 0;

	
	boss.radius = 128;
	boss.HP = 50;
	boss.isAlive = true;
	boss.select = 0;
	boss.selectCount = 860;
	boss.rotateRadius = 0;
	boss.rotateTheta = 0;
	boss.rotatePlus = 100;
	boss.thetaPlus = 0;
	boss.originarRT = { boss.radius,-boss.radius };
	boss.originarRD = { boss.radius,boss.radius };
	boss.originarLT = {-boss.radius,-boss.radius};
	boss.originarLD = {-boss.radius,boss.radius};
	boss.preSelect = 0;
	boss.DrawAngle = 0;
	boss.returnSpeed = 0;
	boss.returnPos = { 0,0 };
	boss.battleStart = false;

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
		beam.EndPos = {0,0};
		beam.flag = false;
		beam.leftDown = { 0,0 };
		beam.leftTop = { 0,0 };
		beam.ob = { 0,0 };
		beam.pos = { 0,0 };
		beam.rightDown = { 0,0 };
		beam.rightTop = { 0,0 };
		beam.theta = 0;
		beam.size = 16;
	
	/*beam.parob = { 0,0 };
	beam.partheta = 0;
	for (int i = 0; i < 30; i++) {
		beam.par[i].isAlive = false;
		beam.par[i].pos = {0,0};
		beam.par[i].size = 8;
		beam.par[i].speed = 0;
		beam.par[i].startPos = {0,0};
		
	}*/
}
void RotatetReset(Boss3& boss) {
	boss.rotateRadius = 0;
	boss.rotatePlus = 0;
	boss.theta = 0;
	boss.rotateTheta = 0;
	boss.leftDown = { boss.pos.x - boss.radius,boss.pos.y + boss.radius };
	boss.rightDown = { boss.pos.x + boss.radius,boss.pos.y + boss.radius };
	boss.leftTop = { boss.pos.x - boss.radius,boss.pos.y - boss.radius };
	boss.rightTop = { boss.pos.x + boss.radius,boss.pos.y - boss.radius };
}
void Boss3BeamReset(BossBeam& beam, BossBeam& beam2) {
	beam.theta = 0;
	beam.count = 0;
	beam.flag = false;
	beam2.theta = 0;
	beam2.flag = false;
	beam2.count = 0;
}
void Boss2BeamReset(BossBeam& beam) {
	beam.theta = 0;
	beam.count = 0;
	beam.flag = false;
}

void BossAtackRotatet(Boss3 &a) {
	
	
	if (a.rotateRadius <= 0) {
		 a.rotatePlus = 1;
		 
	}
	if (a.rotateRadius >= 800) {
		a.rotatePlus = -1;
		
	}
	a.theta += 1.0f/30.0f;
	a.rotateRadius += a.rotatePlus;
	a.pos= { 1280 + cosf(a.theta) * a.rotateRadius,720 + sinf(a.theta) * a.rotateRadius };

	a.rotateTheta += (M_PI) / 60.0f;
	Matrix2x2 rotateMatrix = MakeRotateMatrix(a.rotateTheta);

	a.leftTop = MatrixMultiply(a.originarLT, rotateMatrix);

	a.leftDown = MatrixMultiply(a.originarLD, rotateMatrix);

	a.rightTop = MatrixMultiply(a.originarRT, rotateMatrix);

	a.rightDown = MatrixMultiply(a.originarRD, rotateMatrix);
	a.leftTop = Add(a.leftTop, a.pos);
	a.leftDown = Add(a.leftDown, a.pos);
	a.rightTop = Add(a.rightTop, a.pos);
	a.rightDown = Add(a.rightDown, a.pos);
	

}
void BossBariaCollision(Baria& baria, Vector2& atack, float& radius, int& count, bool& flag) {
	if (flag== true&&count<3) {
		if (RectCollisionHit(baria.pos, baria.Endpos, atack, radius, baria.size) == true) {
			flag = false;
			baria.HP -= 1;
			baria.alpha = 255;
		
		}
	}
	if (baria.HP <= 0) {
		baria.isAlive = false;
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
void Boss1Pattern(Boss3& boss, BossBeam& beam,Vector2 player) {
	if (boss.selectCount > 1000) {

		boss.select = rand() % 3 + 1;
		while (boss.preSelect == boss.select)
		{
			boss.select = rand() % 3 + 1;
		}
		boss.returnSpeed = 0;
		boss.selectCount = 0;
	}
	else {
		boss.selectCount++;
	}
	if (boss.selectCount >= 940) {
		boss.preSelect = boss.select;
		boss.select = 0;
	}
	if (boss.select == 1) {
		Boss2BeamAtack(boss, beam, player);
		boss.returnPos = boss.pos;
	}
	else if (boss.select == 3) {
		BossAtackRotatet(boss);
		boss.returnPos = boss.pos;
	}

	else if (boss.select == 0) {
		if (boss.returnSpeed <= 1.0f) {
			boss.returnSpeed += 1.0f / 30.0f;
		}
		if (boss.returnSpeed >= 1.0f) {
			boss.returnSpeed = 1.0f;
		}
		if (boss.pos.x == 1280) {
			RotatetReset(boss);
		}
		Boss2BeamReset(beam);
		boss.pos = { learp(boss.returnSpeed,boss.returnPos.x , 1280),learp(boss.returnSpeed,boss.returnPos.y , 720) };

	}
}
void Boss2Pattern(Boss3& boss,BossBeam& beam,Vector2 &player,Baria &baria) {
	
	if (boss.selectCount > 1000) {
		
		boss.select = rand() % 3+1;
		while (boss.preSelect == boss.select)
		{
			boss.select = rand() % 3 + 1;
		}
		boss.returnSpeed = 0;
		boss.selectCount = 0;
	}
	
	else {
		boss.selectCount++;
	}
	if (boss.selectCount >= 940) {
		boss.preSelect = boss.select;
		boss.select = 0;
	}
	if (boss.select == 1) {
		Boss2BeamAtack(boss,beam,player);
		boss.returnPos = boss.pos;
	}
	else if (boss.select == 2) {
		BossBaria(boss, baria);
		beam.flag = false;
		boss.returnPos = boss.pos;
	}
	else if (boss.select == 3) {
		BossAtackRotatet(boss);
		boss.returnPos = boss.pos;
	}
	else if (boss.select == 0) {
		if (boss.returnSpeed <= 1.0f) {
			boss.returnSpeed += 1.0f / 30.0f;
		}
		if (boss.returnSpeed >= 1.0f) {
			boss.returnSpeed = 1.0f;
		}
		if (boss.pos.x == 1280) {
			RotatetReset(boss);
		}
		Boss2BeamReset(beam);
		boss.pos = { learp(boss.returnSpeed,boss.returnPos.x , 1280),learp(boss.returnSpeed,boss.returnPos.y , 720) };
	
	}
}

void Boss3Pattern(Boss3& boss, BossBeam& beam,BossBeam& beam2,Vector2& player, Baria& baria) {
	boss.leftDown = { boss.pos.x - boss.radius,boss.pos.y + boss.radius };
	boss.rightDown = { boss.pos.x + boss.radius,boss.pos.y + boss.radius };
	boss.leftTop = { boss.pos.x - boss.radius,boss.pos.y - boss.radius };
	boss.rightTop = { boss.pos.x + boss.radius,boss.pos.y - boss.radius };
	if (boss.selectCount > 1000) {
		while (boss.preSelect == boss.select)
		{
			boss.select = rand() % 5 + 1;
		}
		boss.returnSpeed = 0;
		boss.selectCount = 0;
	}

	else {
		boss.selectCount++;
	}
	if (boss.selectCount >= 940) {
		boss.preSelect = boss.select;
		boss.select = 0;
	}
	if (boss.select == 1||boss.select==4) {
		Boss2BeamAtack(boss, beam, player);
		boss.returnPos = boss.pos;
	}
	else if (boss.select == 2) {
		BossBaria(boss, baria);
		boss.returnPos = boss.pos;
	}
	else if (boss.select == 3) {
		Boss3BeamAtack(boss, beam, beam2, player);
		boss.returnPos = boss.pos;
	}
	else if (boss.select == 5) {
		BossAtackRotatet(boss);
		boss.returnPos = boss.pos;
	}
	else if (boss.select == 0) {
		if (boss.returnSpeed <= 1.0f) {
			boss.returnSpeed += 1.0f / 30.0f;
		}
		if (boss.returnSpeed >= 1.0f) {
			boss.returnSpeed = 1.0f;
		}
		if (boss.pos.x == 1280) {
			RotatetReset(boss);
		}
		Boss3BeamReset(beam,beam2);
		boss.pos = { learp(boss.returnSpeed,boss.returnPos.x , 1280),learp(boss.returnSpeed,boss.returnPos.y , 720) };
	}
}
void Boss2BeamAtack(Boss3& boss, BossBeam& beam ,Vector2& player) {
	beam.count++;
	/*beam.partheta += 1.0f / 20.0f;
	beam.parob = { beam.pos.x + cosf(beam.partheta) * 20,beam.pos.y + sinf(beam.partheta) * 20 };
	for (int i = 0; i < 30; i++) {
		if (beam.par[i].isAlive == false) {
			beam.par[i].pos = beam.parob;
			beam.par[i].startPos = beam.parob;
			beam.par[i].speed = 0;
			beam.par[i].size = 8;
			beam.par[i].isAlive = true;
			break;
		}
		if (beam.par[i].isAlive == true) {
			beam.par[i].speed += 1.0f / 30.0f;
			beam.par[i].pos.x = learp(beam.par[i].speed, beam.par[i].startPos.x, beam.pos.x);
			beam.par[i].pos.y = learp(beam.par[i].speed, beam.par[i].startPos.y, beam.pos.y);
		
		}
		if (beam.par[i].speed >= 1.0f) {
			beam.par[i].isAlive = false;
		}
	}*/
	if (beam.count >= 120) {
		beam.flag = true;
	}
	
	if (beam.count >= 940) {
		beam.flag = false;
		
		beam.theta = 0;
		beam.count = 0;
	}
	

	if (beam.flag == true) {
		beam.pos = boss.pos;
		

		
		beam.theta -= 1.0f / 180.0f;
		beam.ob = { beam.pos.x + cosf(beam.theta) * 40,beam.pos.y + sinf(beam.theta) * 40 };
		Vector2 beamangle = { beam.ob.x - beam.pos.x,beam.ob.y - beam.pos.y };
		Vector2 beamradian = Normalais(beamangle);
		boss.DrawAngle = atan2(beamradian.y, beamradian.x);
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
		Matrix2x2 rotateMatrix = MakeRotateMatrix(boss.DrawAngle);

		boss.leftTop = MatrixMultiply(boss.originarLT, rotateMatrix);

		boss.leftDown = MatrixMultiply(boss.originarLD, rotateMatrix);

		boss.rightTop = MatrixMultiply(boss.originarRT, rotateMatrix);

		boss.rightDown = MatrixMultiply(boss.originarRD, rotateMatrix);
		boss.leftTop = Add(boss.leftTop, boss.pos);
		boss.leftDown = Add(boss.leftDown, boss.pos);
		boss.rightTop = Add(boss.rightTop, boss.pos);
		boss.rightDown = Add(boss.rightDown, boss.pos);
	}
}

void Boss3BeamAtack(Boss3& boss, BossBeam& beam,BossBeam& beam2 ,Vector2& player) {
	beam.count++;
	
	if (beam.count >= 120) {
		beam.flag = true;
	}

	if (beam.count >= 940) {
		beam.flag = false;
		beam2.flag = false;
		beam.theta = 0;
		beam.count = 0;
	}


	if (beam.flag == true) {
		beam.pos = boss.pos;
		beam2.pos = boss.pos;
		beam2.flag = true;
		
		if (player.x >= 1280) {
		beam.theta -= 1.0f / 180.0f;
		}
	else {
			beam.theta += 1.0f / 120.0f;
		}
		beam.ob = { beam.pos.x + cosf(beam.theta) * 40,beam.pos.y + sinf(beam.theta) * 40 };
		Vector2 beamangle = { beam.ob.x - beam.pos.x,beam.ob.y - beam.pos.y };
		Vector2 beamradian = Normalais(beamangle);
		beam.EndPos = Multiply(beamradian, 2000);
		boss.DrawAngle = atan2(beamradian.y, beamradian.x);
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


		Vector2 beam2angle = {  - beamangle.x, - beamangle.y };
		Vector2 beam2radian = Normalais(beam2angle);
		beam2.EndPos = Multiply(beam2radian, 2000);
		beam2.EndPos.x += beam2.pos.x;
		beam2.EndPos.y += beam2.pos.y;

		Vector2 beam2TopAngle = { -beam2radian.y,beam2radian.x };
		Vector2 beam2TopRadian = Multiply(beam2TopAngle, beam.size);
		beam2.leftTop = { beam2.pos.x + beam2TopRadian.x,beam2.pos.y + beam2TopRadian.y };
		beam2.rightTop.x = beam2.EndPos.x + beam2TopRadian.x;
		beam2.rightTop.y = beam2.EndPos.y + beam2TopRadian.y;

		Vector2 beam2DownAngle = { beam2radian.y,-beam2radian.x };
		Vector2 beam2DownRadian = Multiply(beam2DownAngle, beam.size);
		beam2.leftDown = { beam2.pos.x + beam2DownRadian.x,beam2.pos.y + beam2DownRadian.y };
		beam2.rightDown.x = beam2.EndPos.x + beam2DownRadian.x;
		beam2.rightDown.y = beam2.EndPos.y + beam2DownRadian.y;
		
		Matrix2x2 rotateMatrix = MakeRotateMatrix(boss.DrawAngle);

		boss.leftTop = MatrixMultiply(boss.originarLT, rotateMatrix);

		boss.leftDown = MatrixMultiply(boss.originarLD, rotateMatrix);

		boss.rightTop = MatrixMultiply(boss.originarRT, rotateMatrix);

		boss.rightDown = MatrixMultiply(boss.originarRD, rotateMatrix);
		boss.leftTop = Add(boss.leftTop, boss.pos);
		boss.leftDown = Add(boss.leftDown, boss.pos);
		boss.rightTop = Add(boss.rightTop, boss.pos);
		boss.rightDown = Add(boss.rightDown, boss.pos);
	}
}
void BossSetpos(Boss3& boss) {
	if (boss.battleStart == false) {
		boss.returnSpeed += 1.0f / 120.0f;
		boss.pos.y = learp(boss.returnSpeed, -1000, 720);
		boss.pos.x = 1280;
		boss.leftDown = { boss.pos.x - boss.radius,boss.pos.y + boss.radius };
		boss.rightDown = { boss.pos.x + boss.radius,boss.pos.y + boss.radius };
		boss.leftTop = { boss.pos.x - boss.radius,boss.pos.y - boss.radius };
		boss.rightTop = { boss.pos.x + boss.radius,boss.pos.y - boss.radius };
		if (boss.returnSpeed >= 1.0f) {
			boss.battleStart = true;
		}
	}
}