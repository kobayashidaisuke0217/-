#pragma once
#include "Vec2.h"
#define _USE_MATH_DEFINE_
#include <math.h>
float Distance(const Vector2& a, const Vector2& b);
int CircleCollisinHit(const Vector2& a, const float aSize, const Vector2& b, const float bSize);
int CircleCollisinDistance(const Object& a, const Object& b, const int d);