#include "Skydome.h"

void Skydome::Initialize(Model* model) {
    // NULLポインタチェック
    assert(model);

    // メンバ変数に代入
    model_ = model;
    worldTransform_.scale_ = { 100,100,100 };

    // ワールド変換の初期化
    worldTransform_.Initialize();
}

void Skydome::Update() { 
    CreateMatrixUpdate(worldTransform_); 
}

void Skydome::Draw(ViewProjection viewProjection) {
    model_->Draw(worldTransform_, viewProjection);
}