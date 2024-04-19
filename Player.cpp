#include "Player.h"
#include "cassert"

void Player::Intialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
}

void Player::Update() {}

void Player::Draw() {}
