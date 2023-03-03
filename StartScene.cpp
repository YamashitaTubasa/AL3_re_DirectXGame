#include "StartScene.h"
#include "Function.h"
#include <cassert>

void StartScene::Initialize(Model* model, uint32_t textureHandle) {
    // NULL�|�C���^�`�F�b�N
    assert(model);

    // �����o�ϐ��ɑ��
    model_ = model;
    textureHandle_ = textureHandle;

    worldTransform_.translation_ = { 0,0,19 };

    worldTransform_.scale_ = { 15,9,1 };

    // �V���O���g���C���X�^���X���擾����
    input_ = Input::GetInstance();
    debugText_ = DebugText::GetInstance();

    // ���[���h�ϊ��̏�����
    worldTransform_.Initialize();
}

void StartScene::Update() {
    // �s��X�V
    CreateMatrixUpdate(worldTransform_);
}

void StartScene::Draw(ViewProjection viewProjection_) {
    model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}

Vector3  StartScene::GetWorldPosition() {
    //���[���h���W������ϐ�
    Vector3 worldPos;
    //���[���h�s��̕��s�ړ��������擾(���[���h���W)
    worldPos.x = worldTransform_.matWorld_.m[3][0];
    worldPos.y = worldTransform_.matWorld_.m[3][1];
    worldPos.z = worldTransform_.matWorld_.m[3][2];
    return worldPos;
}

void StartScene::OnCollision() {}


float StartScene::GetRadius() {
    return radius_;
}

// �N���A�V�[���ƃ��[���J�����̐e�q�֌W������
void StartScene::SetParent(WorldTransform* worldTransform) {
    worldTransform_.parent_ = worldTransform;
}