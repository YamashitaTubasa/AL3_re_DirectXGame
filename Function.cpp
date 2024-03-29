#include "Function.h"
#include "Enemy.h"

// 単位行列作成
Matrix4 CreateMatIdentity() {
	Matrix4 mat;
	mat.m[0][0] = 1;
	mat.m[1][1] = 1;
	mat.m[2][2] = 1;
	mat.m[3][3] = 1;
	return mat;
}

// スケーリング行列の作成
Matrix4 CreateMatScale(Vector3 scale) {
	Matrix4 mat;
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	mat.m[3][3] = 1.0f;

	return mat;
}

// Z軸の回転行列作成
Matrix4 CreateMatRotationZ(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.z);
	mat.m[0][1] = sin(rotation.z);
	mat.m[1][0] = -sin(rotation.z);
	mat.m[1][1] = cos(rotation.z);

	return mat;
}

// X軸の回転行列作成
Matrix4 CreateMatRotationX(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[1][1] = cos(rotation.x);
	mat.m[1][2] = sin(rotation.x);
	mat.m[2][1] = -sin(rotation.x);
	mat.m[2][2] = cos(rotation.x);

	return mat;
}


// Y軸の回転行列
Matrix4 CreateMatRotationY(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.y);
	mat.m[0][2] = -sin(rotation.y);
	mat.m[2][0] = sin(rotation.y);
	mat.m[2][2] = cos(rotation.y);

	return mat;
}


// 平行移動
Matrix4 CreateMatTranslation(Vector3 translation) {
	Matrix4 lat = CreateMatIdentity();
	lat.m[3][0] = translation.x;
	lat.m[3][1] = translation.y;
	lat.m[3][2] = translation.z;
	lat.m[3][3] = 1;

	return lat;
}

// 行列更新
void CreateMatrixUpdate(WorldTransform& worldTransform_) {

	//スケーリング・回転・平行移動を合成した行列を計算
	worldTransform_.matWorld_ = CreateMatIdentity();
	worldTransform_.matWorld_ *= CreateMatScale(worldTransform_.scale_); // スケーリング行列作成
	worldTransform_.matWorld_ *= CreateMatRotationZ(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationY(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationX(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatTranslation(worldTransform_.translation_);

	if (worldTransform_.parent_ != nullptr) {
		worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	}

	//行列の転送
	worldTransform_.TransferMatrix();
}

// キャラクターの旋回処理
void Rotate(WorldTransform& worldTransform_, Input* input_)
{
	// キャラクターの旋回処理
	Vector3 rotation = { 0,0.1f,0 };
	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_U)) {
		worldTransform_.rotation_ += rotation;
	}
	else if (input_->PushKey(DIK_I)) {
		worldTransform_.rotation_ -= rotation;
	}
}

// 速度ベクトルを自機の向きに合わせて回転させる
Vector3 CreateVector(Vector3 velocity, WorldTransform& worldTransform) {
	Vector3 dirVector;
	dirVector.x = velocity.x * worldTransform.matWorld_.m[0][0] + velocity.y * worldTransform.matWorld_.m[1][0] + velocity.z * worldTransform.matWorld_.m[2][0];
	dirVector.y = velocity.x * worldTransform.matWorld_.m[0][1] + velocity.y * worldTransform.matWorld_.m[1][1] + velocity.z * worldTransform.matWorld_.m[2][1];
	dirVector.z = velocity.x * worldTransform.matWorld_.m[0][2] + velocity.y * worldTransform.matWorld_.m[1][2] + velocity.z * worldTransform.matWorld_.m[2][2];
	return dirVector;
}

// 差分ベクトルを求める
Vector3 Vector3sub(Vector3& v1, Vector3& v2)
{
	Vector3 temp(v2);
	return temp -= v1;
}

// ベクトルの正規化
Vector3 Normalize(Vector3& vector)
{
	float len = length(vector);

	if (len != 0) {
		return vector /= len;
	}

	return vector;
}

float length(Vector3& vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

// 行列とベクトルの掛け算
Vector3 Vector3TransformNormal(Vector3& velocity, Matrix4& mat) {
	Vector3 result;

	result.x = velocity.x * mat.m[0][0] +velocity.y * mat.m[1][0] +velocity.z * mat.m[2][0];
	result.y = velocity.x * mat.m[0][1] +velocity.y * mat.m[1][1] +velocity.z * mat.m[2][1];
	result.z = velocity.x * mat.m[0][2] +velocity.y * mat.m[1][2] +velocity.z * mat.m[2][2];

	return result;
}

