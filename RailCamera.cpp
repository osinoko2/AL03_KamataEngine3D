#include "RailCamera.h"
#include "Function.h"
#include "imgui.h"

void RailCamera::Initialize(const Vector3& position, const Vector3& rotation) {
	// ワールドトランスフォームの初期設定
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;

	// ビュープロジェクションの初期化
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();
}

void RailCamera::Update() {
	worldTransform_.translation_ += Vector3{0.0f, 0.0f, 0.1f};

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	viewProjection_.TransferMatrix();

	// カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -100.0f, 100.0f);
	ImGui::End();
}
