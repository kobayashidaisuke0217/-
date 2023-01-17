#include "Vec2.h"


float Length(const Vector2& a) {
	return sqrtf(a.x * a.x + a.y * a.y);
}
//ベクトルの正規化
Vector2 Normalais(const Vector2& a) {
	float len = Length(a);
	if (len != 0) {
		return { a.x / len,a.y / len };
	}
	return a;
}
//ベクトルの掛け算
Vector2 Multiply(const Vector2& a, float s) {
	return { a.x * s,a.y * s };
}
//ベクトルの引き算
Vector2 Sub(const Vector2& a, const Vector2& b) {
	return { a.x - b.x,a.y - b.y };
}
//ベクトルの足し算
Vector2 Add(const Vector2& a, const Vector2& b) {
	return{ a.x + b.x,a.y + b.y };
}

//外積を求める

Vector2 VectorProduct(const Vector2& a, const Vector2& b) {
	return { a.x - b.x,a.y - b.y };
}
float  Product(const Vector2& a, const Vector2& b,const Vector2&c) {
	Vector2 A= VectorProduct(a, b);
	Vector2 B = VectorProduct(c, a);
	return A.x * B.y - A.y * B.x;
}