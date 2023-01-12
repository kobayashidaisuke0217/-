#include "collision.h"

float Distance(const Vector2& a, const Vector2& b) {
	Vector2 c = { a.x - b.x,a.y - b.y };
	return sqrtf(c.x * c.x + c.y * c.y);
}
int CircleCollisinHit(const Vector2& a, const float aSize, const Vector2& b, const float bSize) {
	float c = Distance(a, b);
	float d = aSize + bSize;
	if (c <= d) {
		return true;
	}
	else {
		return false;
	}
}

int CircleCollisinDistance(const Object& a, const Object& b, const int d) {
	float c = Distance(a.pos, b.pos);

	if (c <= d) {
		return true;
	}
	else {
		return false;
	}
}