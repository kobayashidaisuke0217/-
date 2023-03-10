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
bool RectCollisionHit(const Vector2& start, const Vector2& end, const Vector2& pos, const float& radius, const float& radius2) {
	nLine capsuleLine = { start, end, WHITE };
	Vector2 closestPoint = ClosestPoint(&capsuleLine, &pos);
	Vector2 closestPointToCenter = {
	  pos.x - closestPoint.x, pos.y - closestPoint.y };
	float sumRadius = radius + radius2;
	if (Dot(&closestPointToCenter, &closestPointToCenter) < sumRadius * sumRadius) {
		return true;
	}
	else {
		return false;
	}
}