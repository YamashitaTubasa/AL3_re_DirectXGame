#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include "Player.h"
#include <memory>
#include <list>

class GameScene;

/// <summary>
/// ��Q��
/// </summary>
class Obstacle
{
public: 
	/// <summary>
	/// ������
	/// </summary>
	/// <param name = "model">���f��</param>
	/// <param mame = "textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjectione">�r���[�v���W�F�N�V�����i�Q�Ɠn���j</param>
	void Draw(ViewProjection viewProjection_);

	/// <summary>
	/// �e�̔���
	/// </summary>
	void Fire();

	// ���ˊԊu
	static const int kFireInterval = 70;

	// �ڋ߃t�F�[�Y�̏�����
	void ApproachInitialize();

	void SetPlayer(Player* player) { player_ = player; }

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	bool IsDead() const { return isDead_; }

	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	float GetRadius();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

public:
	// �s���t�F�[�Y
	enum class Phase {
		Approach, // �ڋ߂���
		Leave,    // ���E����
	};

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	// ���͏������邽��
	Input* input_ = nullptr;
	// �f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;
	// �t�F�[�Y
	Phase phase_ = Phase::Approach;
	// �ڋ߃t�F�[�Y�̍X�V
	void AccessPhaseUpdate();
	// ���E�t�F�[�Y�̍X�V
	void EliminationPhaseUpdate();
	// ���˃^�C�}�[
	int32_t fireTimer = 0;
	// ���L����
	Player* player_ = nullptr;
	// ���a
	const float radius_ = 1.0f;
	// �f�X�t���O
	bool isDead_ = false;
	// �Q�[���V�[��
	GameScene* gameScene_ = nullptr;
};
