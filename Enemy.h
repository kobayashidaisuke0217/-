#pragma once
#include "struct.h"

class Enemy {
public:
	Enemy(Circle enemy);


public:
	Circle enemy;

	int enemyAlive;//敵生存フラグ
	int enemyScreenIn;//敵が画面内に居るか
};
