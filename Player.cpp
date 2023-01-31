#include "Player.h"

Player::Player(Circle player,Vector2 scroll) {
	this->player = player;
	scroll = { 0,0 };
	hit = false;
	hitCount = 0;
}

void Player::Move(char keys[], char preKeys[], int leftx, int lefty, Vector2 scrollStart, Vector2 scrollEnd, int scrollMode) {
	if (leftx < -10000 || keys[DIK_A] != 0) {
		player.center.x -= player.speed;
		if (player.center.x >= scrollStart.x && player.center.x <= scrollEnd.x) {
			scroll.x -= player.speed;
		}
	}
	// �E�L�[����������E�ɓ�����
	if (leftx > 10000 || keys[DIK_D] != 0) {
		player.center.x += player.speed;
		if (player.center.x >= scrollStart.x && player.center.x <= scrollEnd.x) {
			scroll.x += player.speed;
		}
	}
	// ��L�[�����������ɓ�����
	if (lefty < -10000 || keys[DIK_W] != 0) {
		player.center.y -= player.speed;
		if (player.center.y >= scrollStart.y && player.center.y <= scrollEnd.y && scrollMode == 1) {
			scroll.y -= player.speed;
		}
	}
	// ���L�[���������牺�ɓ�����
	if (lefty > 10000 || keys[DIK_S] != 0) {
		player.center.y += player.speed;
		if (player.center.y >= scrollStart.y && player.center.y <= scrollEnd.y && scrollMode == 1) {
			scroll.y += player.speed;
		}
	}
}
void Player::Hit() {
	if (hit == true) {
		hitCount++;
	}
	if (hitCount > 20) {
		hit = false;
	}
}