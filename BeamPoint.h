#pragma once
#include "struct.h"

class BeamPoint {
public:
	BeamPoint(Circle beamPoint);


public:
	Circle beamPoint;

	int beamAlive;//�r�[�����˒n�_�̐����t���O
	int beamAtackStart = false;//�r�[���J�n

};
