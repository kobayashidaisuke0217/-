#include "Bullets.h"

Bullets::Bullets(Bullet bullet) {
	this->bullet = bullet;
	bulletAngle = { 0,0 };
	bulletOnFlag = false;//�e�̔���
	bulletInductionOnFlag = false;//�U���t���O
	bulletInductionTimer = 10;//�U������(�����l10)
	bulletEndTimer = 300;//�e���Ŏ���(�����l400)
	bullettimer = 80;

}