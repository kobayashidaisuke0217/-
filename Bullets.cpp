#include "Bullets.h"

Bullets::Bullets(Bullet bullet) {
	this->bullet = bullet;
	bulletAngle = { 0,0 };
	bulletOnFlag = false;//弾の発射
	bulletInductionOnFlag = false;//誘導フラグ
	bulletInductionTimer = 10;//誘導時間(初期値10)
	bulletEndTimer = 300;//弾消滅時間(初期値400)
	bullettimer = 80;

}