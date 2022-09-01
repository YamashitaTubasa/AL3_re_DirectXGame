#include "RailCamera.h"

void RailCamera::Initialize(const Vector3& position, const Vector3& rotation) {
	// ���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.translation_ = position;
	worldTransform_.rotation_ = rotation;

	// �r���[�v���W�F�N�V�����̏�����
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();
}

void RailCamera::Update() {
	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ += Vector3(0, 0, 0.07f);

	/*if (input_->PushKey(DIK_U)) {
		worldTransform_.translation_ += Vector3(0.1f, 0, 0);
	}
	if (input_->PushKey(DIK_I)) {
		worldTransform_.translation_ += Vector3(-0.1f, 0, 0);
	}*/
	// ���[���h�g�����X�t�H�[�����X�V
	UpdateMatrix();
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	viewProjection_.eye.x = worldTransform_.matWorld_.m[3][0];
	viewProjection_.eye.y = worldTransform_.matWorld_.m[3][1];
	viewProjection_.eye.z = worldTransform_.matWorld_.m[3][2];

	// ���[���h�O���x�N�g��
	Vector3 forward(0, 0, 1);
	// ���[���J�����̉�]�𔽉f�i���[���J�����̑O���x�N�g���j
	forward = Vector3TransformNormal(forward, worldTransform_.matWorld_);

	// ���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	forward += viewProjection_.eye;
	viewProjection_.target = forward;

	// ���[���h����x�N�g��
	Vector3 up(0, 1, 0);

	// ���[���J�����̉�]�𔽉f�i���[���J�����̏���x�N�g���j
	viewProjection_.up = Vector3TransformNormal(up, worldTransform_.matWorld_);

	// �r���[�v���W�F�N�V�������X�V
	viewProjection_.UpdateMatrix();

	DebugText* debugText_ = DebugText::GetInstance();

	// �f�o�b�N�p�\��
	/*debugText_->SetPos(20, 100);
	debugText_->Printf(
		"RaolCameera Pos:(%f,%f,%f)", viewProjection_.eye.x,
		viewProjection_.eye.y,
		viewProjection_.eye.z);*/
}

void RailCamera::UpdateMatrix() {
	worldTransform_.matWorld_ = CreateMatIdentity();
	worldTransform_.matWorld_ *= CreateMatScale(worldTransform_.scale_); // �X�P�[�����O�s��쐬
	worldTransform_.matWorld_ *= CreateMatRotationZ(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationY(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatRotationX(worldTransform_.rotation_);
	worldTransform_.matWorld_ *= CreateMatTranslation(worldTransform_.translation_);
}
