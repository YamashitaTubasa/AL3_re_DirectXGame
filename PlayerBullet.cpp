#include "PlayerBullet.h"
#include "Function.h"
#include <assert.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position){
	// NULL�|�C���^�`�F�b�N
	assert(model);
	model_ = model;
	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.png");

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() {
	CreatePartid(worldTransform_);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}