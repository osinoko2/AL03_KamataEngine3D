#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"

/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	const ViewProjection& GetViewProjection() const { return viewProjection_; }



private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// ビュープロジェクション
	ViewProjection viewProjection_;
};
