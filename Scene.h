#pragma once
#include "Player.h"

class Scene {
public:


	void SceneChange(int gamemode, int scrollMode, const int enemyNum,
		Circle enemy, Circle beamPoint, Circle player, Circle nucleus, Line triangle,
		Beam beams, Boss3 lastboss, Baria rasBossBaria);

};