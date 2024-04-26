#include "Player.h"
#include "cassert"

void Player::Intialize(Model* model,ViewProjection* viewProjection) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
}

void Player::Update() {

	// 行列を更新して定数バッファに転送
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {
	model_->Draw(worldTransform_, *viewProjection_); 
}