#include "Vec2.h"


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
float  Product(const Vector2& a, const Vector2& b,const Vector2&c) {
	Vector2 A= VectorProduct(a, b);
	Vector2 B = VectorProduct(c, a);
	return A.x * B.y - A.y * B.x;
}

//����
float Dot(const Vector2* lhs, const Vector2* rhs) { return lhs->x * rhs->x + lhs->y * rhs->y; }

Vector2 ClosestPoint(const nLine* line, const Vector2* point) {
	// �����̃x�N�g��
	Vector2 lineVector = { line->end.x - line->start.x, line->end.y - line->start.y };
	float length = sqrtf(lineVector.x * lineVector.x + lineVector.y * lineVector.y);

	// �P�ʃx�N�g��
	Vector2 unitVector = lineVector;
	if (length != 0.0f) {
		unitVector.x = lineVector.x / length;
		unitVector.y = lineVector.y / length;
	}

	// �n�_����|�C���g�ւ̃x�N�g��
	Vector2 toCenter = { point->x - line->start.x, point->y - line->start.y };

	// ����
	float dot = toCenter.x * unitVector.x + toCenter.y * unitVector.y;

	// �ŋߐړ_���~�̓����ɂ��邩�ǂ����Ŕ���
	dot = fmaxf(0.0f, fminf(dot, length));
	Vector2 closestPoint = { line->start.x + unitVector.x * dot, line->start.y + unitVector.y * dot };
	return closestPoint;
}
