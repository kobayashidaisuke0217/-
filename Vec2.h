#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>


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
float Length(const Vector2& a);
//�x�N�g���̐��K��
Vector2 Normalais(const Vector2& a);
//�x�N�g���̊|���Z
Vector2 Multiply(const Vector2& a, float s);
//�x�N�g���̈����Z
Vector2 Sub(const Vector2& a, const Vector2& b);
//�x�N�g���̑����Z
Vector2 Add(const Vector2& a, const Vector2& b);

//�O�ς����߂�

Vector2 VectorProduct(const Vector2& a, const Vector2& b);
float  Product(const Vector2& a, const Vector2& b);