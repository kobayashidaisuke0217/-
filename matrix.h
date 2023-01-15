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

Matrix2x2 MakeRotateMatrix(float theta);
Vector2 MatrixMultiply(Vector2 vector, Matrix2x2 matrix);
