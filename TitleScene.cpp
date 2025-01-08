#include "TitleScene.h"

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	bgWorldTransform_.Initialize();
	viewProjection_.Initialize();

	bgTitleHandle_ = TextureManager::Load("TitleBg.png");
	
	bgTitlesprite_ = Sprite::Create(bgTitleHandle_, {0, 0});
}

void TitleScene::Update() {
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		finished_ = true;
	}
	// 行列計算
	bgWorldTransform_.UpdateMatrix();
}

void TitleScene::Draw() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	bgTitlesprite_->Draw();

	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();

	Model::PreDraw(commandList);

	Model::PostDraw();
}
