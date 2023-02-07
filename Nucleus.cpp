#include "Nucleus.h"

Nucleus::Nucleus(Circle nucleus) {
	nucleus.center = { 0,0 };
	nucleus.radius = 32.0f;
	nucleus.speed = 0;
	nucleus.color = RED;
	nucleus.HP = 100;
	nucleusSuctionCount = 0;
	max = 12;
	nucleusCountfrag = false;
	nucleusPrePos = { 0,0 };
	nucleusSuctionPos = { 0,0 };
	RespornCount = 0;
	isAlive = true;
	float exterior = { 0 };
	float exterior2 = { 0 };
	float exterior3 = { 0 };

	float enemyexterior;
	float enemyexterior2;
	float enemyexterior3;
	int nucleusSuctionFlag = false;
}