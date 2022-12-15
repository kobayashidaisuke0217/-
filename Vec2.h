#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Novice.h"
#define _USE_MATH_DEFINES
typedef struct Vector2 {
	float x;
	float y;
};

typedef struct Object {
	Vector2 pos;
	Vector2 speed;
	float Size;
};

//�����̌v�Z
float Length(const Vector2& a) {
	return sqrtf(a.x * a.x + a.y * a.y);
}
//�x�N�g���̐��K��
Vector2 Normalais(const Vector2& a) {
	float len = Length(a);
	if (len != 0) {
		return { a.x / len,a.y / len };
	}
	return a;
}
//�x�N�g���̊|���Z
Vector2 Multiply(const Vector2& a, float s) {
	return { a.x * s,a.y * s };
}
//�x�N�g���̈����Z
Vector2 Sub(const Vector2& a, const Vector2& b) {
	return { a.x - b.x,a.y - b.y };
}
//�x�N�g���̑����Z
Vector2 Add(const Vector2& a, const Vector2& b) {
	return{ a.x + b.x,a.y + b.y };
}

//�O�ς����߂�

Vector2 VectorProduct(const Vector2& a, const Vector2& b) {
	return { a.x - b.x,a.y - b.y };
}
float  Product(const Vector2& a, const Vector2& b) {
	return a.x * b.y - a.y * b.x;
}