#include "collisionfunc.h"

float Distance(const Vector2& a, const Vector2& b) {
	Vector2 c = { a.x - b.x,a.y - b.y };
	return sqrtf(c.x * c.x + c.y * c.y);
}
bool CircleCollisinHit(const Vector2& a, const float aSize, const Vector2& b, const float bSize) {
	float c = Distance(a, b);
	float d = aSize + bSize;
	if (c <= d) {
		return true;
	}
	else {
		return false;
	}
}

bool CircleCollisinDistance(const Object& a, const Object& b, const int d) {
	float c = Distance(a.pos, b.pos);

	if (c <= d) {
		return true;
	}
	else {
		return false;
	}
}
bool RectColisionHit(float &a, float &b, float &c, float &d) {
	if (a >= 0.0f && b > 0.0f && c > 0.0f && d > 0.0f || a < 0.0f && b < 0.0f && c < 0.0f && d < 0.0f) {
		return true;
	}
	else {
		return false;
	}
}