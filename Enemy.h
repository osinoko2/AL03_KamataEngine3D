#pragma once
#include <Model.h>
#include <WorldTransform.h>

// 行動フェーズ
enum class Phase {
	Approach, // 接近する
	Leave,    // 離脱する
};

/// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void ApproachUpdate();

	void LeaveUpdate();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:
	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	Vector3 ApproachVelocity_ = {0.0f, 0.0f, -0.1f};
	Vector3 LeaveVelocity_ = {-0.2f, 0.2f, -0.1f};

	// フェーズ
	//Phase Approach;
	//Phase Leave;
	Phase phase_ = Phase::Approach;
};