#include "BeamPoint.h"

BeamPoint::BeamPoint(Circle beamPoint) {
	this->beamPoint = beamPoint;
	beamAlive = true;
	Break = false;
	Resporn = 0;
	spwanCount = 0;
}