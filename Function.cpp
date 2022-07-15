#include "Function.h"
#include "Enemy.h"

// �P�ʍs��쐬
Matrix4 CreateMatIdentity() {
	Matrix4 mat;
	mat.m[0][0] = 1;
	mat.m[1][1] = 1;
	mat.m[2][2] = 1;
	mat.m[3][3] = 1;
	return mat;
}

// �X�P�[�����O�s��̍쐬
Matrix4 CreateMatScale(Vector3 scale) {
	Matrix4 mat;
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	mat.m[3][3] = 1.0f;

	return mat;
}

// Z���̉�]�s��쐬
Matrix4 CreateMatRotationZ(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.z);
	mat.m[0][1] = sin(rotation.z);
	mat.m[1][0] = -sin(rotation.z);
	mat.m[1][1] = cos(rotation.z);

	return mat;
}

// X���̉�]�s��쐬
Matrix4 CreateMatRotationX(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[1][1] = cos(rotation.x);
	mat.m[1][2] = sin(rotation.x);
	mat.m[2][1] = -sin(rotation.x);
	mat.m[2][2] = cos(rotation.x);

	return mat;
}


// Y���̉�]�s��
Matrix4 CreateMatRotationY(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.y);
	mat.m[0][2] = -sin(rotation.y);
	mat.m[2][0] = sin(rotation.y);
	mat.m[2][2] = cos(rotation.y);

	return mat;
}


// ���s�ړ�
Matrix4 CreateMatTranslation(Vector3 translation) {
	Matrix4 lat = CreateMatIdentity();
	lat.m[3][0] = translation.x;
	lat.m[3][1] = translation.y;
	lat.m[3][2] = translation.z;
	lat.m[3][3] = 1;

	return lat;
}

// �s��X�V
void CreateMatrixUpdate(WorldTransform& worldTransform_) {

	//�X�P�[�����O�E��]�E���s�ړ������������s����v�Z
	worldTransform_.matWorld_ = CreateMatIdentity();
	worldTransform_.matWorld_ *= CreateMatScale(worldTransform_.scale_); // �X�P�[�����O�s��쐬
	worldTransform_.matWorld_ *= CreateMatRotationZ(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationY(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationX(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatTranslation(worldTransform_.translation_);

	//�s��̓]��
	worldTransform_.TransferMatrix();
}

// �L�����N�^�[�̐��񏈗�
void Rotate(WorldTransform& worldTransform_, Input* input_)
{
	// �L�����N�^�[�̐��񏈗�
	Vector3 rotation = { 0,0.1f,0 };
	// �����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_U)) {
		worldTransform_.rotation_ += rotation;
	}
	else if (input_->PushKey(DIK_I)) {
		worldTransform_.rotation_ -= rotation;
	}
}

// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
Vector3 CreateVector(Vector3 velocity, WorldTransform& worldTransform) {
	Vector3 dirVector;
	dirVector.x = velocity.x * worldTransform.matWorld_.m[0][0] + velocity.y * worldTransform.matWorld_.m[1][0] + velocity.z * worldTransform.matWorld_.m[2][0];
	dirVector.y = velocity.x * worldTransform.matWorld_.m[0][1] + velocity.y * worldTransform.matWorld_.m[1][1] + velocity.z * worldTransform.matWorld_.m[2][1];
	dirVector.z = velocity.x * worldTransform.matWorld_.m[0][2] + velocity.y * worldTransform.matWorld_.m[1][2] + velocity.z * worldTransform.matWorld_.m[2][2];
	return dirVector;
}

