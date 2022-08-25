#include "Skydome.h"

void Skydome::Initialize(Model* model) {
    // NULL�|�C���^�`�F�b�N
    assert(model);

    // �����o�ϐ��ɑ��
    model_ = model;
    worldTransform_.scale_ = { 100,100,100 };

    // ���[���h�ϊ��̏�����
    worldTransform_.Initialize();
}

void Skydome::Update() { 
    CreateMatrixUpdate(worldTransform_); 
}

void Skydome::Draw(ViewProjection viewProjection) {
    model_->Draw(worldTransform_, viewProjection);
}