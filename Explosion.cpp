#include "Explosion.h"

Explosion::Explosion() {
	pos = { -100,-100 };
	explosionTimer = 130;
	explosionFlag = false;
	explosionCount = 0;
	enemyAlphaTimer = 255;
	explosion = Novice::LoadTexture("./Resources/image/Explosion.png");
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
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 0, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 120 && explosionTimer > 110) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 64, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 100 && explosionTimer > 90) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 128, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 90 && explosionTimer > 80) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 192, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 80 && explosionTimer > 70) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 256, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 70 && explosionTimer > 60) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 320, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 60 && explosionTimer > 50) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 384, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 50 && explosionTimer > 40) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 448, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 40 && explosionTimer > 30) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 512, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 30 && explosionTimer > 20) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 576, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 20 && explosionTimer > 10) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 640, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
		if (explosionTimer <= 10 && explosionTimer > 0) {
			Novice::DrawSpriteRect(pos.x - scroll.x, pos.y - scroll.y, 704, 0, 64, 64, explosion, 0.07, 1, 0.0f, 0xFFFFFFFF);
		}
	}
}