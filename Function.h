#pragma once
#include <Vector3.h>
#include <Matrix4x4.h>

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

float Length(const Vector3& v);

Vector3 Normalize(const Vector3& v);

Matrix4x4 Inverse(const Matrix4x4& m);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);