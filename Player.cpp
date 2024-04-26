#include "Player.h"
#include "cassert"

void Player::Intialize(Model* model, uint32_t textureHandle ,ViewProjection* viewProjection) {
	// NULLポインタチェック
	assert(model);

	//model_ = model;
	textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;

	worldTransform_.Initialize();
}

void Player::Update() {

	worldTransform_.TransferMatrix();
	// 行列を更新して定数バッファに転送
	//worldTransform_.UpdateMatrix();
}

void Player::Draw() {
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_); 
}