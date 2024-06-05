#include "Player.h"
#include "Function.h"
#include <cassert>
#include "ImGuiManager.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() {
	// キャラクター旋回処理
	Rotate();

	// キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更 (左右)
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	// 〃 (上下)
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	// 座標移動
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// 移動限界座標
	const float kMoveLimitX = 34.0f;
	const float kMoveLimitY = 19.0f;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// キャラクター攻撃処理
	Attack();

	// 弾更新
	for (PlayerBullet *bullet : bullets_) {
		bullet->Update();
	}

	// キャラクターの座標を画面表示する処理
	ImGui::Begin(" ");
	ImGui::SliderFloat3("Player", &worldTransform_.translation_.x, -40.0f, 40.0f);
	ImGui::End();

	// アフィン変換行列の作成
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾描画
	for (PlayerBullet *bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		// 弾があれば解放する
		/*if (bullet_) {
			delete bullet_;
			bullet_ = nullptr;
		}*/

		// 自キャラの座標をコピー
		//DirectX::XMFLOAT3 position = worldTransform_.translation_;

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		// 弾の登録する
		bullets_.push_back(newBullet);
	}
}

Player::~Player() {
	// bullet_の解放
	for (PlayerBullet * bullet : bullets_) {
		delete bullet;
	}
	bullets_.clear();
}

void Player::Rotate() {
	// 回転速さ
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}
