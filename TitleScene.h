#pragma once
#include "DirectXCommon.h"
#include "GameScene.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "TextureManager.h"
/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsFinished() const { return finished_; }

private:
	bool finished_ = false;
	DirectXCommon* dxCommon_ = nullptr;
	WorldTransform bgWorldTransform_;
	ViewProjection viewProjection_;
	uint32_t bgTitleHandle_ = 0u;
	Sprite* bgTitlesprite_ = nullptr;
};