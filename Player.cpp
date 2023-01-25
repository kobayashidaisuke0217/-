#include "Player.h"

Player::Player(Circle player) {
	this->player = player;
}

void Player::Move(char keys[], char preKeys[], int leftx, int lefty, Vector2 scrollStart, Vector2 scrollEnd, Vector2 scroll, int scrollMode) {
	if (leftx < -10000 || keys[DIK_A] != 0) {
		player.center.x -= player.speed;
		if (player.center.x >= scrollStart.x && player.center.x <= scrollEnd.x) {
			scroll.x -= player.speed;
		}
	}
	// 右キーを押したら右に動かす
	if (leftx > 10000 || keys[DIK_D] != 0) {
		player.center.x += player.speed;
		if (player.center.x >= scrollStart.x && player.center.x <= scrollEnd.x) {
			scroll.x += player.speed;
		}
	}
	// 上キーを押したら上に動かす
	if (lefty < -10000 || keys[DIK_W] != 0) {
		player.center.y -= player.speed;
		if (player.center.y >= scrollStart.y && player.center.y <= scrollEnd.y && scrollMode == 1) {
			scroll.y -= player.speed;
		}
	}
	// 下キーを押したら下に動かす
	if (lefty > 10000 || keys[DIK_S] != 0) {
		player.center.y += player.speed;
		if (player.center.y >= scrollStart.y && player.center.y <= scrollEnd.y && scrollMode == 1) {
			scroll.y += player.speed;
		}
	}
}