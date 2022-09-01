#include "ClearScene.h"
#include "Function.h"
#include <cassert>

void ClearScene::Initialize(Model* model, uint32_t textureHandle) {
    // NULLポインタチェック
    assert(model);

    // メンバ変数に代入
    model_ = model;
    textureHandle_ = textureHandle;

    worldTransform_.translation_ = { 0,0,19 };

    worldTransform_.scale_ = { 15,9,1 };

    // シングルトンインスタンスを取得する
    input_ = Input::GetInstance();
    debugText_ = DebugText::GetInstance();

    // ワールド変換の初期化
    worldTransform_.Initialize();
}

void ClearScene::Update() {
    // 行列更新
    CreateMatrixUpdate(worldTransform_);
}

void ClearScene::Draw(ViewProjection viewProjection_) {
    model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

Vector3  ClearScene::GetWorldPosition() {
    //ワールド座標を入れる変数
    Vector3 worldPos;
    //ワールド行列の平行移動成分を取得(ワールド座標)
    worldPos.x = worldTransform_.matWorld_.m[3][0];
    worldPos.y = worldTransform_.matWorld_.m[3][1];
    worldPos.z = worldTransform_.matWorld_.m[3][2];
    return worldPos;
}

void ClearScene::OnCollision() {}


float ClearScene::GetRadius() {
    return radius_;
}

// クリアシーンとレールカメラの親子関係を結ぶ
void ClearScene::SetParent(WorldTransform* worldTransform) {
    worldTransform_.parent_ = worldTransform;
}
