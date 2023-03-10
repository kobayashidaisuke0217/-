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

typedef struct Beam {
	Vector2 pos;
	Vector2 EndPos;
	Vector2 angle;
	float size;
	Vector2  radian;
	Vector2 flag;
	
};

typedef struct nLine {
	Vector2 start;
	Vector2 end;
	unsigned int color;
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
float  Product(const Vector2& a, const Vector2& b,const Vector2&c);
//内積
float Dot(const Vector2* lhs, const Vector2* rhs);
Vector2 ClosestPoint(const nLine* line, const Vector2* point);

Vector2 vectorInverse(const Vector2& v, const Vector2& a, const Vector2& b);