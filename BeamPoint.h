#pragma once
#include "struct.h"

class BeamPoint {
public:
	BeamPoint(Circle beamPoint);


public:
	Circle beamPoint;

	int beamAlive;//ビーム発射地点の生存フラグ
	int beamAtackStart = false;//ビーム開始

};
