#include "Skydome.h"

void Skydome::Initialize(Model* model, ViewProjection* viewProjection) {

	viewProjection_ = viewProjection;
	model_ = model;
	worldTransform_.Initialize();
}

void Skydome::Update() { worldTransform_.TransferMatrix(); }

void Skydome::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}
