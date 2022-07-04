#include "Player.h"
#include "Function.h"
#include <cassert>


void Player::Initialize(Model* model, uint32_t textureHandle) {
    // NULL�|�C���^�`�F�b�N
    assert(model);

    model_ = model;
    textureHandle_ = textureHandle; 

    // �V���O���g���C���X�^���X���擾����
    input_ = Input::GetInstance();
    debugText_ = DebugText::GetInstance();

    worldTransform_.Initialize();
}

void Player::Update() {
    // �L�����N�^�[�̈ړ��x�N�g��
    Vector3 move = { 0,0,0 };

    //�L�����N�^�[�̈ړ��̑���
    const float kCharacterSpeed = 0.3f;


    // �ړ��x�N�g����ύX���鏈��
    if (input_->PushKey(DIK_LEFT)) {
        move.x -= kCharacterSpeed;
    }
    if (input_->PushKey(DIK_RIGHT)) {
        move.x += kCharacterSpeed;
    }
    if (input_->PushKey(DIK_UP)) {
        move.y += kCharacterSpeed;
    }
    if (input_->PushKey(DIK_DOWN)) {
        move.y -= kCharacterSpeed;
    }
    
    // ���W�ړ�(�x�N�g���̉��Z)
    
    // �ړ����E���W
    const float kMoveLimitX = 35;
    const float kMoveLimitY = 18;

    // �͈͂𒴂��Ȃ�����worldTrandform_.translation_�l�ɐ�����������
    worldTransform_.translation_.x= max(worldTransform_.translation_.x, -kMoveLimitX);
    worldTransform_.translation_.x= min(worldTransform_.translation_.x, +kMoveLimitX);
    worldTransform_.translation_.y= max(worldTransform_.translation_.y, -kMoveLimitY);
    worldTransform_.translation_.y= min(worldTransform_.translation_.y, +kMoveLimitY);

    worldTransform_.translation_ += move;


    // �s��X�V
    worldTransform_.matWorld_ = CreateMatIdentity();
    worldTransform_.matWorld_ *= CreateMatScale(worldTransform_.scale_);
    worldTransform_.matWorld_ *= CreateMatRotationX(worldTransform_.rotation_);
    worldTransform_.matWorld_ *= CreateMatRotationY(worldTransform_.rotation_);
    worldTransform_.matWorld_ *= CreateMatRotationZ(worldTransform_.rotation_);
    worldTransform_.matWorld_ *= CreateMatTranslation(worldTransform_.translation_);
    worldTransform_.TransferMatrix();

}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}