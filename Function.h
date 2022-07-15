#include "worldTransform.h"
#include "Input.h"
#include "Enemy.h"
#include <math.h>

// �P�ʍs��쐬
Matrix4 CreateMatIdentity();

// �X�P�[�����O�s��̍쐬
Matrix4 CreateMatScale(Vector3 scale);

// Z���̉�]�s��쐬
Matrix4 CreateMatRotationZ(Vector3 rotation);

// X���̉�]�s��쐬
Matrix4 CreateMatRotationX(Vector3 rotation);

// Y���̉�]�s��
Matrix4 CreateMatRotationY(Vector3 rotation);

// ���s�ړ�
Matrix4 CreateMatTranslation(Vector3 translation);

// ���[���h�g�����X�t�H�[���̍X�V
void CreateMatrixUpdate(WorldTransform& worldTransform_);

// �L�����N�^�[�̐��񏈗�
void Rotate(WorldTransform& worldTransform_, Input* input_);

// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
Vector3 CreateVector(Vector3 velocity, WorldTransform& worldTransform);

