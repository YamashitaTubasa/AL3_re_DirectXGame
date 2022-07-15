#include "Enemy.h"
#include "Function.h"
#include <cassert>

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
    // NULLポインタチェック
    assert(model);

    // メンバ変数に代入
    model_ = model;
    textureHandle_ = textureHandle;

    // シングルトンインスタンスを取得する
    input_ = Input::GetInstance();
    debugText_ = DebugText::GetInstance();

    // ワールド変換の初期化
    worldTransform_.Initialize();
}

void Enemy::Update() {

    // キャラクターの移動ベクトル
    Vector3 move = { 0,0,0 };

    //キャラクターの移動の速さ
    const float EnemySpeed = 0.3f;
    const float EnemyYSpeed = 0.01f;
    const float accessPhaseSpeed = 0.3f; // 接近フェーズのスピード
    const float eliminationPhaseSpeed = 0.3f; // 離脱フェーズの速度

    // 座標移動(ベクトルの加算)
    /*move.z -= EnemySpeed;
    move.y += EnemyYSpeed;*/

    /* worldTransform_.translation_ += move;*/

    // 行列更新
    CreateMatrixUpdate(worldTransform_);

    switch (phase_) {
    case Enemy::Phase::Approach:
    default:
        // 接近フェーズの更新
        AccessPhaseUpdate();
        break;
    case Enemy::Phase::Leave:
        // 離脱フェーズの更新
        EliminationPhaseUpdate();
        break;
    }
}

void Enemy::Draw(ViewProjection viewProjection_) {
    model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

// 接近フェーズの更新
void Enemy::AccessPhaseUpdate() {
    // 移動 (ベクトルを加算)
    worldTransform_.translation_ -= {0.0, 0.0, 0.05};
    //規定の位置に到達したら離脱
    if (worldTransform_.translation_.z < -10.0f) {
        phase_ = Enemy::Phase::Leave;
    }
}

// 離脱フェーズの更新
void Enemy::EliminationPhaseUpdate() {
    // 移動（ベクトルを加算）
    worldTransform_.translation_ += {0.05, 0.05, 0};
}
