#include "Beams.h"

Beams::Beams(Beam beam) {
	this->beam = beam;

	beemStart = { 0 };
	atackFlag = { false };
	beamMode = 0;//0�ŏ\���A1�œガ����
	preAtack = false;
	atackCount = 0;
	preCount = 0;
	beamSize = 32;//�r�[���̑���
	beamAttackchange = 0;//�r�[���U���̏ꏊ�ύX
}