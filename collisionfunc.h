#pragma once
#include "Vec2.h"
#define _USE_MATH_DEFINE_
#include <math.h>
float Distance(const Vector2& a, const Vector2& b);
bool CircleCollisinHit(const Vector2& a, const float aSize, const Vector2& b, const float bSize);
bool CircleCollisinDistance(const Object& a, const Object& b, const int d);
bool RectCollisionHit(const Vector2& start, const Vector2& end, const Vector2& pos, const float& radius, const float& radius2);