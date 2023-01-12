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

//長さの計算
float Length(const Vector2& a);
//ベクトルの正規化
Vector2 Normalais(const Vector2& a);
//ベクトルの掛け算
Vector2 Multiply(const Vector2& a, float s);
//ベクトルの引き算
Vector2 Sub(const Vector2& a, const Vector2& b);
//ベクトルの足し算
Vector2 Add(const Vector2& a, const Vector2& b);

//外積を求める

Vector2 VectorProduct(const Vector2& a, const Vector2& b);
float  Product(const Vector2& a, const Vector2& b);