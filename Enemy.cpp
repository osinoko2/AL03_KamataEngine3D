#include "Enemy.h"
#include "TextureManager.h"
#include <cassert>
#include "Function.h"
#include "Player.h"

void Enemy::Initialize(Model* model, const Vector3& position) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("Enemy.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 接近フェーズ初期化
	ApproachInitialize();
}

void Enemy::ApproachInitialize() {
	// 発射タイマーを初期化
	fireTimer = kFireInterval;
}

void Enemy::Update() {
	

	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	switch (phase_) {
	case Phase::Approach:
	default:
		ApproachUpdate();

		break;
	case Phase::Leave:
		LeaveUpdate();
		break;
	}
	
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.UpdateMatrix();
}

void Enemy::ApproachUpdate() {
	// 移動
	worldTransform_.translation_.x += ApproachVelocity_.x;
	worldTransform_.translation_.y += ApproachVelocity_.y;
	worldTransform_.translation_.z += ApproachVelocity_.z;

	// 発射タイマーカウントダウン
	fireTimer--;

	// 指定時間に達した
	if (fireTimer == 0) {
		// 弾を発射
		Fire();
		// 発射タイマーを初期化
		fireTimer = kFireInterval;
	}

	// 規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
	//worldTransform_.UpdateMatrix();
}

void Enemy::LeaveUpdate() {
	// 移動
	worldTransform_.translation_.x += LeaveVelocity_.x;
	worldTransform_.translation_.y += LeaveVelocity_.y;
	worldTransform_.translation_.z += LeaveVelocity_.z;

	//worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Fire() {
	assert(player_);

	// 弾の速さ (調整項目)
	//const float kBulletSpeed = 1.0f;
	
	Vector3 PlayerPosition = player_->GetWorldPosition();
	Vector3 EnemyPosition = GetWorldPosition();
	Vector3 DifferenceVector;
	DifferenceVector.x = PlayerPosition.x - EnemyPosition.x;
	DifferenceVector.y = PlayerPosition.y - EnemyPosition.y;
	DifferenceVector.z = PlayerPosition.z - EnemyPosition.z;
	Vector3 ADVector = Normalize(DifferenceVector);
	BulletVelocity_ = ADVector;


	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(bulletmodel_, worldTransform_.translation_, BulletVelocity_);

	// 弾の登録する
	bullets_.push_back(newBullet);
}

Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	//bullets_.clear();

	delete bulletmodel_;
}

void Enemy::OnCollision() {}

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
