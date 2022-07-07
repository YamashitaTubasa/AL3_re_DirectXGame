#include "Function.h"
#include "worldTransform.h"
#include <math.h>

/// 単位行列作成
Matrix4 CreateMatIdentity() {
	Matrix4 mat;
	mat.m[0][0] = 1;
	mat.m[1][1] = 1;
	mat.m[2][2] = 1;
	mat.m[3][3] = 1;
	return mat;
}

/// スケーリング行列の作成
Matrix4 CreateMatScale(Vector3 scale) {
	Matrix4 mat;
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	mat.m[3][3] = 1.0f;

	return mat;
}

/// Z軸の回転行列作成
Matrix4 CreateMatRotationZ(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.z);
	mat.m[0][1] = sin(rotation.z);
	mat.m[1][0] = -sin(rotation.z);
	mat.m[1][1] = cos(rotation.z);

	return mat;
}

/// X軸の回転行列作成
Matrix4 CreateMatRotationX(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[1][1] = cos(rotation.x);
	mat.m[1][2] = sin(rotation.x);
	mat.m[2][1] = -sin(rotation.x);
	mat.m[2][2] = cos(rotation.x);

	return mat;
}


/// Y軸の回転行列
Matrix4 CreateMatRotationY(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.y);
	mat.m[0][2] = -sin(rotation.y);
	mat.m[2][0] = sin(rotation.y);
	mat.m[2][2] = cos(rotation.y);

	return mat;
}


/// 平行移動
Matrix4 CreateMatTranslation(Vector3 translation) {
	Matrix4 lat = CreateMatIdentity();
	lat.m[3][0] = translation.x;
	lat.m[3][1] = translation.y;
	lat.m[3][2] = translation.z;
	lat.m[3][3] = 1;

	return lat;
}

void CreatePartid(WorldTransform& worldTransform_) {

	//スケーリング・回転・平行移動を合成した行列を計算
	worldTransform_.matWorld_ = CreateMatIdentity();
	worldTransform_.matWorld_ *= CreateMatScale(worldTransform_.scale_); // スケーリング行列作成
	worldTransform_.matWorld_ *= CreateMatRotationZ(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationY(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationX(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatTranslation(worldTransform_.translation_);

	//行列の転送
	worldTransform_.TransferMatrix();
}

void Rotate(WorldTransform& worldTransform_, Input* input_) {
	// キャラクターの旋回処理
	Vector3 turn = { 0,0.1f,0 };
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_U)) {
		worldTransform_.rotation_ += turn;
	}
	else if (input_->PushKey(DIK_I)) {
		worldTransform_.rotation_ -= turn;
	}
}