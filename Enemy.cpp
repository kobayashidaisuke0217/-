#include "Enemy.h"

Enemy::Enemy(Circle enemy) {
	this->enemy = enemy;

	enemyAlive = true;
	enemyScreenIn = false;
}