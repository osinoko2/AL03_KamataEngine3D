#pragma once
#include <Vector3.h>
#include <Matrix4x4.h>

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
