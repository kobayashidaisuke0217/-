#pragma once
#include <Novice.h>
#include <assert.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include "Vec2.h"
typedef struct Matrix3x3 {
	float m[3][3];
};
typedef struct Matrix2x2 {
	float m[2][2];
};
//Matrix3x3 makeTranslateMatrix(Vector2 translate);
//Vector2 Transform(Vector2 vector, Matrix3x3 matrix);
//Matrix3x3 MakeRotateMatrix(float theta);
//Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

//Matrix3x3 makeTranslateMatrix(Vector2 translate) {
//	Matrix3x3 result;
//	result.m[0][0] = 1;
//	result.m[0][1] = 0;
//	result.m[0][2] = 0;
//	result.m[1][0] = 0;
//	result.m[1][1] = 1;
//	result.m[1][2] = 0;
//	result.m[2][0] = translate.x;
//	result.m[2][1] = translate.y;
//	result.m[2][2] = 1;
//	return result;
//}
//Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
//	Vector2 result;
//	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
//	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
//	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
//	assert(w != 0.0f);
//	result.x /= w;
//	result.y /= w;
//	return result;
//}
//
//Matrix3x3 MakeRotateMatrix(float theta) {
//	Matrix3x3 result;
//	result.m[0][0] = cosf(theta);
//	result.m[0][1] = sinf(theta);
//	result.m[0][2] = 0;
//	result.m[1][0] = -sinf(theta);
//	result.m[1][1] = cosf(theta);
//	result.m[1][2] = 0;
//	result.m[2][0] = 0;
//	result.m[2][1] = 0;
//	result.m[2][2] = 1;
//	return result;
//}
//Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
//	Matrix3x3 result;
//	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
//	result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
//	result.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];
//	result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
//	result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
//	result.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];
//	result.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
//	result.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
//	result.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];
//	return result;
//}

Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 result;
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);
	return result;
}
Vector2 MatrixMultiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];
	return result;
}
