#pragma once
#include "struct.h"

class Bullets {
public:
	Bullets(Bullet bullet);


public:
	Bullet bullet;

	Vector2 bulletAngle;

	int bulletOnFlag;//弾の発射
	int bulletInductionOnFlag;//誘導フラグ
	int bulletInductionTimer;//誘導時間(初期値100)
	int bulletEndTimer;//弾消滅時間(初期値400)
	int bullettimer;//弾の発射クールダウン
};
