#pragma once
#include "struct.h"

class Bullets {
public:
	Bullets(Bullet bullet);


public:
	Bullet bullet;

	Vector2 bulletAngle;

	int bulletOnFlag;//�e�̔���
	int bulletInductionOnFlag;//�U���t���O
	int bulletInductionTimer;//�U������(�����l100)
	int bulletEndTimer;//�e���Ŏ���(�����l400)
	int bullettimer;//�e�̔��˃N�[���_�E��
};
