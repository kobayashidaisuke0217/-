#include "Nucleus.h"

Nucleus::Nucleus(Circle nucleus) {
	nucleus.center = { 0,0 };
	nucleus.radius = 36.0f;
	nucleus.speed = 0;
	nucleus.color = RED;
	nucleus.HP = 100;
	nucleusSuctionCount = 0;
	max = 12;
	nucleusCountfrag = false;
	nucleusPrePos = { 0,0 };
	nucleusSuctionPos = { 0,0 };
}