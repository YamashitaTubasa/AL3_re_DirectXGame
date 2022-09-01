#include "RailCamera.h"

void RailCamera::Initialize(const Vector3& position, const Vector3& rotation) {
	// ワールドトランスフォームの初期設定
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;

	// ビュープロジェクションの初期化
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();
}

void RailCamera::Update() {
	// 移動（ベクトルを加算）
	worldTransform_.translation_ += Vector3(0, 0, 0.07f);

	/*if (input_->PushKey(DIK_U)) {
		worldTransform_.translation_ += Vector3(0.1f, 0, 0);
	}
	if (input_->PushKey(DIK_I)) {
		worldTransform_.translation_ += Vector3(-0.1f, 0, 0);
	}*/
	// ワールドトランスフォームを更新
	UpdateMatrix();
	// ワールド行列の平行移動成分を取得（ワールド座標）
	viewProjection_.eye.x = worldTransform_.matWorld_.m[3][0];
	viewProjection_.eye.y = worldTransform_.matWorld_.m[3][1];
	viewProjection_.eye.z = worldTransform_.matWorld_.m[3][2];

	// ワールド前方ベクトル
	Vector3 forward(0, 0, 1);
	// レールカメラの回転を反映（レールカメラの前方ベクトル）
	forward = Vector3TransformNormal(forward, worldTransform_.matWorld_);

	// 視点から前方に適当な距離進んだ位置が注視点
	forward += viewProjection_.eye;
	viewProjection_.target = forward;

	// ワールド上方ベクトル
	Vector3 up(0, 1, 0);

	// レールカメラの回転を反映（レールカメラの上方ベクトル）
	viewProjection_.up = Vector3TransformNormal(up, worldTransform_.matWorld_);

	// ビュープロジェクションを更新
	viewProjection_.UpdateMatrix();

	DebugText* debugText_ = DebugText::GetInstance();

	// デバック用表示
	/*debugText_->SetPos(20, 100);
	debugText_->Printf(
		"RaolCameera Pos:(%f,%f,%f)", viewProjection_.eye.x,
		viewProjection_.eye.y,
		viewProjection_.eye.z);*/
}

void RailCamera::UpdateMatrix() {
	worldTransform_.matWorld_ = CreateMatIdentity();
	worldTransform_.matWorld_ *= CreateMatScale(worldTransform_.scale_); // スケーリング行列作成
	worldTransform_.matWorld_ *= CreateMatRotationZ(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationY(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationX(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatTranslation(worldTransform_.translation_);
}
