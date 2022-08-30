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

// �����x�N�g�������߂�
Vector3 Vector3sub(Vector3& v1, Vector3& v2);

// �x�N�g���̐��K��
Vector3 Normalize(Vector3& vec);

float length(Vector3& vec);

Vector3 Vector3TransformNormal(Vector3& velocity, Matrix4& mat);