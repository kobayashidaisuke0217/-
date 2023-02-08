#include "Explosion.h"

Explosion::Explosion() {
	pos = { -100,-100 };
	explosionTimer = 130;
	explosionFlag = false;
	explosionCount = 0;
	enemyAlphaTimer = 255;
	ex[0] = Novice::LoadTexture("./Resources/image/Explosion.png");
	ex[1] = Novice::LoadTexture("./Resources/image/Explosion2.png");
	ex[2] = Novice::LoadTexture("./Resources/image/Explosion3.png");
	ex[3] = Novice::LoadTexture("./Resources/image/Explosion4.png");
	ex[4] = Novice::LoadTexture("./Resources/image/Explosion5.png");
	ex[5] = Novice::LoadTexture("./Resources/image/Explosion6.png");
	ex[6] = Novice::LoadTexture("./Resources/image/Explosion7.png");
	ex[7] = Novice::LoadTexture("./Resources/image/Explosion8.png");
	ex[8] = Novice::LoadTexture("./Resources/image/Explosion9.png");
	ex[9] = Novice::LoadTexture("./Resources/image/Explosion10.png");
	ex[10] = Novice::LoadTexture("./Resources/image/Explosion11.png");
	ex[11] = Novice::LoadTexture("./Resources/image/Explosion12.png");
	ex[12] = Novice::LoadTexture("./Resources/image/Explosion13.png");
}

void Explosion::Update() {
	if (explosionFlag == true) {
		explosionTimer--;
		enemyAlphaTimer-=0.7;
	}
	if (explosionTimer <= 0) {
		explosionCount++;
		explosionTimer = 130;
	}
	if (explosionCount >= 3) {
		explosionFlag = false;
	}
}

void Explosion::Draw(Vector2 scroll) {
	if (explosionFlag == true) {
		if (explosionTimer <= 130 && explosionTimer > 120) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[0], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 120 && explosionTimer > 110) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[1], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 100 && explosionTimer > 90) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[2], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 90 && explosionTimer > 80) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[3], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 80 && explosionTimer > 70) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[4], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 70 && explosionTimer > 60) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[5], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 60 && explosionTimer > 50) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[6], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 50 && explosionTimer > 40) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[7], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 40 && explosionTimer > 30) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[8], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 30 && explosionTimer > 20) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[9], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 20 && explosionTimer > 10) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[10], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 10 && explosionTimer > 0) {
			Novice::DrawSprite(pos.x - scroll.x, pos.y - scroll.y, ex[11], 2, 2, 0.0f, 0xFFFFFFFF);
		}
		
	}
}