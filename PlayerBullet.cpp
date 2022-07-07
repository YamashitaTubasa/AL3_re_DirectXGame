#include "PlayerBullet.h"
#include "Function.h"
#include <assert.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position){
	// NULLポインタチェック
	assert(model);
	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("black.png");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() {
	CreatePartid(worldTransform_);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}