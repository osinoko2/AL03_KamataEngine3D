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
	void Initialize(WorldTransform& worldTransform, ViewProjection& viewProjection);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	const WorldTransform& GetWorldTransform() { return *worldTransform_; }

	const ViewProjection& GetViewProjection() { return *viewProjection_; }

	const Matrix4x4 GetMatView() { return viewProjection_->matView; }

	const Matrix4x4 GetmatProjection() { return viewProjection_->matProjection; }

private:
	// ワールド変換データ
	WorldTransform* worldTransform_;

	// ビュープロジェクション
	ViewProjection* viewProjection_;
};
