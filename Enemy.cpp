#include "Enemy.h"
#include "Function.h"
#include <cassert>

void Enemy::Initialize(Model* model, uint32_t textureHandle) {
    // NULL�|�C���^�`�F�b�N
    assert(model);

    // �����o�ϐ��ɑ��
    model_ = model;
    textureHandle_ = textureHandle;

    // �V���O���g���C���X�^���X���擾����
    input_ = Input::GetInstance();
    debugText_ = DebugText::GetInstance();

    // ���[���h�ϊ��̏�����
    worldTransform_.Initialize();
}

void Enemy::Update() {

    // �L�����N�^�[�̈ړ��x�N�g��
    Vector3 move = { 0,0,0 };

    //�L�����N�^�[�̈ړ��̑���
    const float EnemySpeed = 0.3f;
    const float EnemyYSpeed = 0.01f;

    // ���W�ړ�(�x�N�g���̉��Z)

    move.z -= EnemySpeed;
    move.y += EnemyYSpeed;

    worldTransform_.translation_ += move;
    const float accessPhaseSpeed = 0.3f; // �ڋ߃t�F�[�Y�̃X�s�[�h
    const float eliminationPhaseSpeed = 0.3f; // ���E�t�F�[�Y�̑��x
    // �s��X�V
    worldTransform_.matWorld_ = CreateMatIdentity();
    worldTransform_.matWorld_ *= CreateMatScale(worldTransform_.scale_);
    worldTransform_.matWorld_ *= CreateMatRotationX(worldTransform_.rotation_);
    worldTransform_.matWorld_ *= CreateMatRotationY(worldTransform_.rotation_);
    worldTransform_.matWorld_ *= CreateMatRotationZ(worldTransform_.rotation_);
    worldTransform_.matWorld_ *= CreateMatTranslation(worldTransform_.translation_);
    worldTransform_.TransferMatrix();

    switch (phase_) {
    case Enemy::Phase::Approach:
    default:
        // �ړ� (�x�N�g�������Z)
        worldTransform_.translation_ += move;
        // ����̈ʒu�ɓ��B�����痣�E
        if (worldTransform_.translation_.z < 0.0f) {
            phase_ = Enemy::Phase::Leave;
        }
        break;
    case Enemy::Phase::Leave:
        // �ړ��i�x�N�g�������Z�j
        worldTransform_.translation_ += move;
        break;
    }
}

void Enemy::Draw(ViewProjection viewProjection_) {
    model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}
