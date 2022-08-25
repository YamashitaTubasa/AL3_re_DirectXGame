#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include "ViewProjection.h"
#include "Function.h"
#include <memory>
#include <list>
#include <cassert>

/// <summary>
/// �V��
/// </summary>
class Skydome
{
public:
    /// <summary>
    /// ������
    /// </summary>
    void Initialize(Model* model);

    /// <summary>
    /// �X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw(ViewProjection viewProjection);
    
private:
    // ���[���h�ϊ��f�[�^
    WorldTransform worldTransform_;
    // ���f��
    Model* model_ = nullptr;
};
