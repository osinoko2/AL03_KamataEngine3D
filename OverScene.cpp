#include "OverScene.h"

void OverScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	EnterWorldTransform_.Initialize();
	viewProjection_.Initialize();
	// 天球の生成
	skydome_ = new Skydome();
	// 天球の初期化
	skydome_->Initialize(modelSkydome_, &viewProjection_);

	bgHandle_ = TextureManager::Load("DeathScene.png");

	Bgsprite_ = Sprite::Create(bgHandle_, Vector2{0, 0});
}

void OverScene::Update() {

	// 天球の更新
	skydome_->Update();
}

void OverScene::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	Sprite::PreDraw(commandList);

	Bgsprite_->Draw();

	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();

	Model::PreDraw(commandList);

	Model::PostDraw();
}
