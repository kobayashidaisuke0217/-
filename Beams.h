#pragma once
#include "Vec2.h"

class Beams {
public:
	Beams(Beam beam);


public:
	Beam beam;
	Beam BTop;
	Beam BDown;

	Vector2 beemStart = { 0 };

	int atackFlag;
	int beamMode;//0�ŏ\���A1�œガ����
	int preAtack;
	int atackCount;
	int preCount;
	int beamSize;//�r�[���̑���
	int beamAttackchange;//�r�[���U���̏ꏊ�ύX

};
