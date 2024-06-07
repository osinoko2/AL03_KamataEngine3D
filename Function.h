#pragma once
#include <Vector3.h>
#include <Matrix4x4.h>

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

// ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);