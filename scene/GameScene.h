#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Skydome.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>
#include "DebugCamera.h"
#include "Function.h"
#include "MapChipFeild.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 3Dモデルデータ
	Model* model_ = nullptr;
	Model* modelBlock_ = nullptr;
	Model* modelSkydome_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 自キャラ
	Player* player_ = nullptr;

	// 天球
	Skydome* skydome_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	std::vector <std::vector< WorldTransform* >> worldTransformBlocks_;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// マップチップフィールド
	MapChipFeild* mapChipField_;

	void GenerateBlocks();

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
