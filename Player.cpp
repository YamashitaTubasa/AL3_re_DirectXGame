#include "Player.h"
#include "Function.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textureHandle) {
    // NULLポインタチェック
    assert(model);

    model_ = model;
    textureHandle_ = textureHandle; 

    // シングルトンインスタンスを取得する
    input_ = Input::GetInstance();
    debugText_ = DebugText::GetInstance();
    
    // ワールド変換の初期化
    worldTransform_.Initialize();
}

void Player::Update() {
    // キャラクターの移動ベクトル
    Vector3 move = { 0,0,0 };

    //キャラクターの移動の速さ
    const float characterSpeed = 0.3f;

    // 移動ベクトルを変更する処理
    if (input_->PushKey(DIK_LEFT)) {
        move.x -= characterSpeed;
    }
    if (input_->PushKey(DIK_RIGHT)) {
        move.x += characterSpeed;
    }
    if (input_->PushKey(DIK_UP)) {
        move.y += characterSpeed;
    }
    if (input_->PushKey(DIK_DOWN)) {
        move.y -= characterSpeed;
    }

    // 座標移動(ベクトルの加算)

    // 移動限界座標
    const float kMoveLimitX = 35;
    const float kMoveLimitY = 19;

    // 範囲を超えない処理worldTrandform_.translation_値に制限をかける
    worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
    worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
    worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
    worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
    worldTransform_.translation_ += move;

    // 行列更新
    worldTransform_.matWorld_ = CreateMatIdentity();
    worldTransform_.matWorld_ *= CreateMatScale(worldTransform_.scale_);
    worldTransform_.matWorld_ *= CreateMatRotationX(worldTransform_.rotation_);
    worldTransform_.matWorld_ *= CreateMatRotationY(worldTransform_.rotation_);
    worldTransform_.matWorld_ *= CreateMatRotationZ(worldTransform_.rotation_);
    worldTransform_.matWorld_ *= CreateMatTranslation(worldTransform_.translation_);
    worldTransform_.TransferMatrix();

    // キャラクターの旋回処理
    Rotate(worldTransform_, input_);

    // キャラクター攻撃処理
    Attack();

    // 弾更新
    if (bullet_) {
        bullet_->Update();
    }
}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

    // 弾描画
    if (bullet_) {
        bullet_->Draw(viewProjection_);
    }
}

void Player::Attack() {
    if (input_->PushKey(DIK_SPACE)) {
        // 弾を生成し、初期化
        PlayerBullet* newBullet = new PlayerBullet();
        newBullet->Initialize(model_, worldTransform_.translation_);

        // 球を登録する
        bullet_ = newBullet;
    }
}