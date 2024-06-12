#pragma once
#include <Model.h>
#include <WorldTransform.h>
#include "EnemyBullet.h"
#include <list>

// 自機クラスの前方宣言
class Player;

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

	// 接近フェーズ初期化
	void ApproachInitialize();

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

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	void SetPlayer(Player* player) { player_ = player; }

	// 発射間隔
	static const int kFireInterval = 60;

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
	Vector3 BulletVelocity_ = {0.0f, 0.0f, -1.0f};

	// フェーズ
	Phase phase_ = Phase::Approach;

	// 弾
	std::list<EnemyBullet*> bullets_;

	// 発射タイマー
	int32_t fireTimer = 0;

	// 自キャラ
	Player* player_ = nullptr;

	// ワールド座標を取得
	Vector3 GetWorldPosition();
};