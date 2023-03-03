#include "Obstacle.h"
#include "Function.h"
#include <cassert>

void Obstacle::Initialize(Model* model, uint32_t textureHandle) {
    // NULL�|�C���^�`�F�b�N
    assert(model);

    // �����o�ϐ��ɑ��
    model_ = model;
    textureHandle_ = textureHandle;

    // ��Q���̉�]
    worldTransform_.rotation_ = { 0, 0, 0 };

    // ��Q���̈ʒu
    worldTransform_.translation_ = { 0,0,100 };

    // �V���O���g���C���X�^���X���擾����
    input_ = Input::GetInstance();
    debugText_ = DebugText::GetInstance();

    // ���[���h�ϊ��̏�����
    worldTransform_.Initialize();

    // �ڋ߃t�F�[�Y�̏�����
    ApproachInitialize();
}

void Obstacle::Update() {
    //// �f�X�t���O�̗������e���폜
    //bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
    //    return bullet->IsDead();
    //    });

    // �L�����N�^�[�̈ړ��x�N�g��
    Vector3 move = { 0,0,0 };

    //�L�����N�^�[�̈ړ��̑���
    const float EnemySpeed = 0.3f;
    const float EnemyYSpeed = 0.01f;
    const float accessPhaseSpeed = 0.3f; // �ڋ߃t�F�[�Y�̃X�s�[�h
    const float eliminationPhaseSpeed = 0.3f; // ���E�t�F�[�Y�̑��x

    // ���W�ړ�(�x�N�g���̉��Z)
    /*move.z -= EnemySpeed;
    move.y += EnemyYSpeed;*/

    /* worldTransform_.translation_ += move;*/

    // �s��X�V
    CreateMatrixUpdate(worldTransform_);

    switch (phase_) {
    case Obstacle::Phase::Approach:
    default:
        // �ڋ߃t�F�[�Y�̍X�V
        AccessPhaseUpdate();
        break;
    case Obstacle::Phase::Leave:
        // ���E�t�F�[�Y�̍X�V
        EliminationPhaseUpdate();
        break;
    }

}

void Obstacle::Draw(ViewProjection viewProjection_) {
    model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

void Obstacle::Fire() {
    //assert(player_);

    //// �e�̑��x
    //const float kBulletSpeed = 1.0f;
    //Vector3 velocity(0, 0, kBulletSpeed);

    //// ���@�L�����̃��[���h���W���擾
    //Vector3 playerPos = player_->GetWorldPosition();
    //// �G�L�����̃��[���h���W���擾
    //Vector3 enemyPos = this->GetWorldPosition();
    //// �G�L���������L�����̍����x�N�g�������߂�
    //Vector3 vector = playerPos;
    //vector -= enemyPos;
    //float length = (float)std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    //// �x�N�g���̐��K��
    //if (length != 0) {
    //    vector /= length;
    //}
    //// �x�N�g���̒������A�����ɍ��킹��
    //velocity = vector;

    //// ���L�����̍��W���R�s�[
    //Vector3 position = worldTransform_.translation_;

    //// �e�𐶐����A������
    //std::unique_ptr<EnemyBullet>newBullet = std::make_unique<EnemyBullet>();
    //newBullet->Initialize(model_, position, velocity);

    //// ����o�^����
    //bullets_.push_back(std::move(newBullet));
}

// �ڋ߃t�F�[�Y�̍X�V
void Obstacle::AccessPhaseUpdate() {
    // �ړ� (�x�N�g�������Z)
    if (worldTransform_.translation_.z <= 100 && worldTransform_.translation_.z > 80) {
        worldTransform_.translation_ -= {0.0, 0.0, 0.05};
    }

    if (worldTransform_.translation_.z < 80 && worldTransform_.translation_.z > 60) {
        worldTransform_.translation_ -= {0.05, 0.0, 0.05};
    }

    if (worldTransform_.translation_.z < 60 && worldTransform_.translation_.z > 40) {
        worldTransform_.translation_ -= {-0.05, 0.03, 0.05};
    }

    if (worldTransform_.translation_.z < 40 && worldTransform_.translation_.z > 20) {
        /*worldTransform_.translation_ -= {-0.1, 0.0, 0.05};*/
        worldTransform_.translation_ = { 0,0,100 };
    }

    if (worldTransform_.translation_.z < 20 && worldTransform_.translation_.z >= 0) {
        worldTransform_.translation_ -= {-0.05, -0.05, 0.05};
    }
    /*worldTransform_.translation_ -= {0.0, 0.0, 0.05};*/
    //�K��̈ʒu�ɓ��B�����痣�E
    if (worldTransform_.translation_.z < 0.0f) {
        phase_ = Obstacle::Phase::Leave;
    }
    // ���˃^�C�}�[�J�E���g�_�E��
    fireTimer--;

    // �w�莞�ԂɒB����
    if (fireTimer <= 0) {
        // �e�𔭎�
        Fire();
        // ���˃^�C�}�[��������
        fireTimer = kFireInterval;
    }
    /*if (input_->TriggerKey(DIK_R)) {
        worldTransform_.translation_ = { 0,0,100 };
    }*/
}

// �ڋ߃t�F�[�Y�̏�����
void Obstacle::ApproachInitialize() {
    // ���˃^�C�}�[��������
    fireTimer = kFireInterval;
}

// ���E�t�F�[�Y�̍X�V
void Obstacle::EliminationPhaseUpdate() {
    // �ړ��i�x�N�g�������Z�j
    if (worldTransform_.translation_.y < 0) {
        worldTransform_.translation_ += {0.05, 0.05, 0};
    }
    if (worldTransform_.translation_.y > 0) {
        worldTransform_.translation_ += {-0.05, 0.05, 0};
    }
    if (worldTransform_.translation_.y > 50) {
        worldTransform_.translation_ += {-0.05, -0.05, 0};
    }

    // ���˃^�C�}�[�J�E���g�_�E��
    fireTimer--;

    // �w�莞�ԂɒB����
    if (fireTimer <= 0) {
        // �e�𔭎�
        Fire();
        // ���˃^�C�}�[��������
        fireTimer = kFireInterval;
    }
}

Vector3 Obstacle::GetWorldPosition() {
    //���[���h���W������ϐ�
    Vector3 worldPos;
    //���[���h�s��̕��s�ړ��������擾(���[���h���W)
    worldPos.x = worldTransform_.matWorld_.m[3][0];
    worldPos.y = worldTransform_.matWorld_.m[3][1];
    worldPos.z = worldTransform_.matWorld_.m[3][2];
    return worldPos;
}

void Obstacle::OnCollision() {
    isDead_ = true;
}

float Obstacle::GetRadius() {
    return radius_;
}