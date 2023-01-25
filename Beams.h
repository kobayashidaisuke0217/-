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
	int beamMode;//0で十字、1で薙ぎ払い
	int preAtack;
	int atackCount;
	int preCount;
	int beamSize;//ビームの太さ
	int beamAttackchange;//ビーム攻撃の場所変更

};
