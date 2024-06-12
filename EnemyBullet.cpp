#include "EnemyBullet.h"
#include "TextureManager.h"
#include <cassert>
#include "Function.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);
	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("Explosion.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void EnemyBullet::Update() {
	// 座標を移動させる
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(ViewProjection& viewProjection) {
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 EnemyBullet::GetBulletPosition() {
	// ワールド座標を入れる変数
	Vector3 bulletPos;

	// ワールド行列の平行移動成分を取得
	bulletPos.x = worldTransform_.matWorld_.m[3][0];
	bulletPos.y = worldTransform_.matWorld_.m[3][1];
	bulletPos.z = worldTransform_.matWorld_.m[3][2];

	return bulletPos;
}

void EnemyBullet::OnCollision() { isDead_ = true; }
