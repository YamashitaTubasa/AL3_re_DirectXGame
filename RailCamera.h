#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include "Function.h"
#include "Input.h"

/// <summary>
/// ���[���J����
/// </summary>
class RailCamera
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name = "position">�������W</param>
	/// <param name = "rotation">�����p�x</param>
	void Initialize(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �s��
	/// </summary>
	void UpdateMatrix();

	/// <summary>
	/// �r���[�v���W�F�N�V�������擾
	/// </summary>
	/// <returns>�r���[�v���W�F�N�V����</returna>
	const ViewProjection& GetViewProjection() { return viewProjection_; }

	// ���[���h�s����擾
	WorldTransform* GetWorldMatrix() { return &worldTransform_; }

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// �r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;
	// ���͏������邽��
	Input* input_ = nullptr;
};

