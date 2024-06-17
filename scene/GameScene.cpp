#include "GameScene.h"
#include "AxisIndicator.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include "Function.h"
#include <math.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete EnemyModel_;
	delete modelSkygdome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("Rock.png");

	// 3Dモデルの生成
	model_ = Model::Create();
	EnemyModel_ = Model::Create();
	modelSkygdome_ = Model::CreateFromOBJ("skydome3", true);

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// 自キャラの生成
	player_ = new Player();

	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);

	// 敵の生成
	enemy_ = new Enemy();

	// 敵の初期化
	enemy_->Initialize(EnemyModel_, EnemyPosition);

	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	// 天球の生成
	skydome_ = new Skydome();

	// 天球の初期化
	skydome_->Initialize(modelSkygdome_, &viewProjection_);

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);

	// 軸方向表示が参照するビュープロジェクションを指定する (アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// ビュープロジェクションの初期化
	viewProjection_.farZ = 10.0f;
	viewProjection_.Initialize();
}

void GameScene::Update() {

	// 自キャラの更新
	player_->Update();

	// 敵の更新
	if (enemy_) {
		enemy_->Update(); 
	}

	// 天球の更新
	skydome_->Update();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = true;
	}
#endif

	// カメラの処理
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetMatView();
		viewProjection_.matProjection = debugCamera_->GetmatProjection();
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		// ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}

	CheckAllCollisions();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 敵の描画
	if (enemy_) {
		enemy_->Draw(viewProjection_);
	}

	// 天球の描画
	skydome_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	// 敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	#pragma region 自キャラと敵弾の当たり判定

	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		// 敵弾の座標
		posB = bullet->GetBulletPosition();

		Vector3 distance;
		distance.x = posB.x - posA.x;
		distance.y = posB.y - posA.y;
		distance.z = posB.z - posA.z;


		// 球と球の交差判定
		if (sqrtf(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z) <= 1.0f) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定

	// 敵キャラの座標
	posB = enemy_->GetWorldPosition();

	// 自弾全てと敵キャラの当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		// 自弾の座標
		posA = bullet->GetBulletPosition();

		Vector3 distance;
		distance.x = posB.x - posA.x;
		distance.y = posB.y - posA.y;
		distance.z = posB.z - posA.z;

		if (sqrtf(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z) <= 1.0f) {
			// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
		}
	}

	#pragma endregion

	#pragma region 自弾と敵弾の当たり判定

	for (PlayerBullet* shotbullet : playerBullets) {
		for (EnemyBullet* firebullet : enemyBullets) {
			// 自弾の座標
			posA = shotbullet->GetBulletPosition();

			// 敵弾の座標
			posB = firebullet->GetBulletPosition();

			Vector3 distance;
			distance.x = posB.x - posA.x;
			distance.y = posB.y - posA.y;
			distance.z = posB.z - posA.z;

			if (sqrtf(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z) <= 1.0f) {
				// 自弾の衝突時コールバックを呼び出す
				shotbullet->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				firebullet->OnCollision();
			}
		}
	}

	#pragma endregion
}
