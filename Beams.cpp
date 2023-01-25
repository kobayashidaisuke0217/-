#include "Beams.h"

Beams::Beams(Beam beam) {
	this->beam = beam;

	beemStart = { 0 };
	atackFlag = { false };
	beamMode = 0;//0で十字、1で薙ぎ払い
	preAtack = false;
	atackCount = 0;
	preCount = 0;
	beamSize = 32;//ビームの太さ
	beamAttackchange = 0;//ビーム攻撃の場所変更
}