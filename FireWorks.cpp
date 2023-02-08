#include "FireWorks.h"

FireWorks::FireWorks() {
	fireWorksCenter = { -100,-100,12,0,0,WHITE };
	fireWorksAlpha = 255;
	fireTimer = 90;
	fireFlag = false;
	startFlag = true;
	for (int i = 0; i < 64; i++) {
		fireWorks[i] = { fireWorksCenter.center.x,fireWorksCenter.center.y,fireWorksCenter.radius,0,0,WHITE };
	}

}

void FireWorks::Update(char keys[]) {
	if (startFlag == true) {
		for (int i = 0; i < 64; i++) {
			fireWorks[i].center = fireWorksCenter.center;
		}
		fireTimer = 90;
		fireWorksAlpha = 255;
		fireFlag = true;
		fireWorksCenter.speed = { 3,3 };
		startFlag = false;
	}

	fireWorksAlpha -= 2;

	if (fireWorksAlpha <= 0) {
		fireWorksAlpha = 0;
	}

	if (fireFlag == true) {
		fireTimer--;
	}

	if (fireTimer <= 60) {
		fireWorksCenter.speed = { 2,2 };
	}

	if (fireTimer <= 30) {
		fireWorksCenter.speed = { 1,1 };
	}

	if (fireTimer <= 0) {
		fireFlag = false;
		fireWorksCenter.speed = { 0.5,0.5 };
	}

	if (fireFlag == false && fireWorksAlpha <= 0) {
		fireTimer++;
	}

	if (fireFlag == false && fireTimer >= 60) {
		startFlag = true;
	}

	if (fireTimer < 90) {
		//9Žž‚Ì•ûŒü‚©‚çŽžŒv‰ñ‚è‚ÅŽw’è
		fireWorks[0].center.x -= fireWorksCenter.speed.x;
		fireWorks[1].center.x -= fireWorksCenter.speed.x / 1.4;
		fireWorks[2].center.x -= fireWorksCenter.speed.x / 2;
		fireWorks[3].center.x -= fireWorksCenter.speed.x / 3.5;

		fireWorks[4].center.x -= fireWorksCenter.speed.x;
		fireWorks[5].center.x -= fireWorksCenter.speed.x / 1.4;
		fireWorks[6].center.x -= fireWorksCenter.speed.x / 2;
		fireWorks[7].center.x -= fireWorksCenter.speed.x / 3.5;
		fireWorks[4].center.y -= fireWorksCenter.speed.y / 2;
		fireWorks[5].center.y -= fireWorksCenter.speed.y / 2 / 1.4;
		fireWorks[6].center.y -= fireWorksCenter.speed.y / 2 / 2;
		fireWorks[7].center.y -= fireWorksCenter.speed.y / 2 / 3.5;

		fireWorks[8].center.x -= fireWorksCenter.speed.x;
		fireWorks[8].center.y -= fireWorksCenter.speed.y;
		fireWorks[9].center.x -= fireWorksCenter.speed.x / 1.4;
		fireWorks[9].center.y -= fireWorksCenter.speed.y / 1.4;
		fireWorks[10].center.x -= fireWorksCenter.speed.x / 2;
		fireWorks[10].center.y -= fireWorksCenter.speed.y / 2;
		fireWorks[11].center.x -= fireWorksCenter.speed.x / 3.5;
		fireWorks[11].center.y -= fireWorksCenter.speed.y / 3.5;

		fireWorks[12].center.x -= fireWorksCenter.speed.x / 2;
		fireWorks[12].center.y -= fireWorksCenter.speed.y;
		fireWorks[13].center.x -= fireWorksCenter.speed.x / 2 / 1.4;
		fireWorks[13].center.y -= fireWorksCenter.speed.y / 1.4;
		fireWorks[14].center.x -= fireWorksCenter.speed.x / 2 / 2;
		fireWorks[14].center.y -= fireWorksCenter.speed.y / 2;
		fireWorks[15].center.x -= fireWorksCenter.speed.x / 2 / 3.5;
		fireWorks[15].center.y -= fireWorksCenter.speed.y / 3.5;

		fireWorks[16].center.y -= fireWorksCenter.speed.y;
		fireWorks[17].center.y -= fireWorksCenter.speed.y / 1.4;
		fireWorks[18].center.y -= fireWorksCenter.speed.y / 2;
		fireWorks[19].center.y -= fireWorksCenter.speed.y / 3.5;

		fireWorks[20].center.x += fireWorksCenter.speed.x / 2;
		fireWorks[21].center.x += fireWorksCenter.speed.x / 2 / 1.4;
		fireWorks[22].center.x += fireWorksCenter.speed.x / 2 / 2;
		fireWorks[23].center.x += fireWorksCenter.speed.x / 2 / 3.5;
		fireWorks[20].center.y -= fireWorksCenter.speed.y;
		fireWorks[21].center.y -= fireWorksCenter.speed.y / 1.4;
		fireWorks[22].center.y -= fireWorksCenter.speed.y / 2;
		fireWorks[23].center.y -= fireWorksCenter.speed.y / 3.5;

		fireWorks[24].center.x += fireWorksCenter.speed.x;
		fireWorks[24].center.y -= fireWorksCenter.speed.y;
		fireWorks[25].center.x += fireWorksCenter.speed.x / 1.4;
		fireWorks[25].center.y -= fireWorksCenter.speed.y / 1.4;
		fireWorks[26].center.x += fireWorksCenter.speed.x / 2;
		fireWorks[26].center.y -= fireWorksCenter.speed.y / 2;
		fireWorks[27].center.x += fireWorksCenter.speed.x / 3.5;
		fireWorks[27].center.y -= fireWorksCenter.speed.y / 3.5;

		fireWorks[28].center.x += fireWorksCenter.speed.x;
		fireWorks[28].center.y -= fireWorksCenter.speed.y / 2;
		fireWorks[29].center.x += fireWorksCenter.speed.x / 1.4;
		fireWorks[29].center.y -= fireWorksCenter.speed.y / 2 / 1.4;
		fireWorks[30].center.x += fireWorksCenter.speed.x / 2;
		fireWorks[30].center.y -= fireWorksCenter.speed.y / 2 / 2;
		fireWorks[31].center.x += fireWorksCenter.speed.x / 3.5;
		fireWorks[31].center.y -= fireWorksCenter.speed.y / 2 / 3.5;

		fireWorks[32].center.x += fireWorksCenter.speed.x;
		fireWorks[33].center.x += fireWorksCenter.speed.x / 1.4;
		fireWorks[34].center.x += fireWorksCenter.speed.x / 2;
		fireWorks[35].center.x += fireWorksCenter.speed.x / 3.5;

		fireWorks[36].center.x += fireWorksCenter.speed.x;
		fireWorks[37].center.x += fireWorksCenter.speed.x / 1.4;
		fireWorks[38].center.x += fireWorksCenter.speed.x / 2;
		fireWorks[39].center.x += fireWorksCenter.speed.x / 3.5;
		fireWorks[36].center.y += fireWorksCenter.speed.y / 2;
		fireWorks[37].center.y += fireWorksCenter.speed.y / 2 / 1.4;
		fireWorks[38].center.y += fireWorksCenter.speed.y / 2 / 2;
		fireWorks[39].center.y += fireWorksCenter.speed.y / 2 / 3.5;

		fireWorks[40].center.x += fireWorksCenter.speed.x;
		fireWorks[40].center.y += fireWorksCenter.speed.y;
		fireWorks[41].center.x += fireWorksCenter.speed.x / 1.4;
		fireWorks[41].center.y += fireWorksCenter.speed.y / 1.4;
		fireWorks[42].center.x += fireWorksCenter.speed.x / 2;
		fireWorks[42].center.y += fireWorksCenter.speed.y / 2;
		fireWorks[43].center.x += fireWorksCenter.speed.x / 3.5;
		fireWorks[43].center.y += fireWorksCenter.speed.y / 3.5;

		fireWorks[44].center.x += fireWorksCenter.speed.x / 2;
		fireWorks[44].center.y += fireWorksCenter.speed.y;
		fireWorks[45].center.x += fireWorksCenter.speed.x / 2 / 1.4;
		fireWorks[45].center.y += fireWorksCenter.speed.y / 1.4;
		fireWorks[46].center.x += fireWorksCenter.speed.x / 2 / 2;
		fireWorks[46].center.y += fireWorksCenter.speed.y / 2;
		fireWorks[47].center.x += fireWorksCenter.speed.x / 2 / 3.5;
		fireWorks[47].center.y += fireWorksCenter.speed.y / 3.5;

		fireWorks[48].center.y += fireWorksCenter.speed.y;
		fireWorks[49].center.y += fireWorksCenter.speed.y / 1.4;
		fireWorks[50].center.y += fireWorksCenter.speed.y / 2;
		fireWorks[51].center.y += fireWorksCenter.speed.y / 3.5;

		fireWorks[52].center.x -= fireWorksCenter.speed.x / 2;
		fireWorks[53].center.x -= fireWorksCenter.speed.x / 2 / 1.4;
		fireWorks[54].center.x -= fireWorksCenter.speed.x / 2 / 2;
		fireWorks[55].center.x -= fireWorksCenter.speed.x / 2 / 3.5;
		fireWorks[52].center.y += fireWorksCenter.speed.y;
		fireWorks[53].center.y += fireWorksCenter.speed.y / 1.4;
		fireWorks[54].center.y += fireWorksCenter.speed.y / 2;
		fireWorks[55].center.y += fireWorksCenter.speed.y / 3.5;

		fireWorks[56].center.x -= fireWorksCenter.speed.x;
		fireWorks[56].center.y += fireWorksCenter.speed.y;
		fireWorks[57].center.x -= fireWorksCenter.speed.x / 1.4;
		fireWorks[57].center.y += fireWorksCenter.speed.y / 1.4;
		fireWorks[58].center.x -= fireWorksCenter.speed.x / 2;
		fireWorks[58].center.y += fireWorksCenter.speed.y / 2;
		fireWorks[59].center.x -= fireWorksCenter.speed.x / 3.5;
		fireWorks[59].center.y += fireWorksCenter.speed.y / 3.5;

		fireWorks[60].center.x -= fireWorksCenter.speed.x;
		fireWorks[60].center.y += fireWorksCenter.speed.y / 2;
		fireWorks[61].center.x -= fireWorksCenter.speed.x / 1.4;
		fireWorks[61].center.y += fireWorksCenter.speed.y / 2 / 1.4;
		fireWorks[62].center.x -= fireWorksCenter.speed.x / 2;
		fireWorks[62].center.y += fireWorksCenter.speed.y / 2 / 2;
		fireWorks[63].center.x -= fireWorksCenter.speed.x / 3.5;
		fireWorks[63].center.y += fireWorksCenter.speed.y / 2 / 3.5;

		for (int i = 0; i < 64; i++) {
			fireWorks[i].center.y += 1.0;
		}
	}
}

void FireWorks::Draw(int color) {
	//Novice::DrawEllipse(fireWorksCenter.center.x, fireWorksCenter.center.y, fireWorksCenter.radius, fireWorksCenter.radius, 0.0f, fireWorksCenter.color, kFillModeSolid);
	for (int i = 0; i < 64; i++) {
		Novice::DrawEllipse(fireWorks[i].center.x, fireWorks[i].center.y, fireWorks[i].radius, fireWorks[i].radius, 0.0f, color, kFillModeSolid);
	}
}