#include "Enemy.h"
#include "TextureManager.h"
#include <cassert>

void Enemy::Initialize(Model* model, const Vector3& position) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("Enemy.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void Enemy::Update() {
	switch (phase_) {
	case Phase::Approach:
	default:
		ApproachUpdate();
		break;
	case Phase::Leave:
		LeaveUpdate();
		break;
	}

	worldTransform_.UpdateMatrix();
}

void Enemy::ApproachUpdate() {
	// 移動
	worldTransform_.translation_.x += ApproachVelocity_.x;
	worldTransform_.translation_.y += ApproachVelocity_.y;
	worldTransform_.translation_.z += ApproachVelocity_.z;
	// 規定の位置に到達したら離脱
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
	worldTransform_.UpdateMatrix();
}

void Enemy::LeaveUpdate() {
	// 移動
	worldTransform_.translation_.x += LeaveVelocity_.x;
	worldTransform_.translation_.y += LeaveVelocity_.y;
	worldTransform_.translation_.z += LeaveVelocity_.z;

	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
