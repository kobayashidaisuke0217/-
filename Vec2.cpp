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

//内積
float Dot(const Vector2* lhs, const Vector2* rhs) { return lhs->x * rhs->x + lhs->y * rhs->y; }

Vector2 ClosestPoint(const nLine* line, const Vector2* point) {
	// 直線のベクトル
	Vector2 lineVector = { line->end.x - line->start.x, line->end.y - line->start.y };
	float length = sqrtf(lineVector.x * lineVector.x + lineVector.y * lineVector.y);

	// 単位ベクトル
	Vector2 unitVector = lineVector;
	if (length != 0.0f) {
		unitVector.x = lineVector.x / length;
		unitVector.y = lineVector.y / length;
	}

	// 始点からポイントへのベクトル
	Vector2 toCenter = { point->x - line->start.x, point->y - line->start.y };

	// 内積
	float dot = toCenter.x * unitVector.x + toCenter.y * unitVector.y;

	// 最近接点が円の内部にいるかどうかで判定
	dot = fmaxf(0.0f, fminf(dot, length));
	Vector2 closestPoint = { line->start.x + unitVector.x * dot, line->start.y + unitVector.y * dot };
	return closestPoint;
}
