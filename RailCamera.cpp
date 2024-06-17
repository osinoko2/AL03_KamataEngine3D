#include "RailCamera.h"
#include "Function.h"
#include "imgui.h"

void RailCamera::Initialize(WorldTransform& worldTransform, ViewProjection& viewProjection) {
	// ワールドトランスフォームの初期設定
	worldTransform_ = &worldTransform;
	viewProjection_ = &viewProjection;

	// ビュープロジェクションの初期化
	viewProjection_->Initialize();
}

void RailCamera::Update() {
	worldTransform_->translation_.z -= 1.0f;

	worldTransform_->rotation_.y += 0.001f;

	worldTransform_->UpdateMatrix();

	//worldTransform_->matWorld_ = MakeAffineMatrix(worldTransform_->scale_, worldTransform_->rotation_, worldTransform_->translation_);

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_->matView = Inverse(worldTransform_->matWorld_);

	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", &worldTransform_->translation_.x, 0.0f, 1.0f);
	ImGui::SliderFloat3("rotation", &worldTransform_->rotation_.x, 0.0f, 1.0f);
	ImGui::End();
}
