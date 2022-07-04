#include "worldTransform.h"
/// �P�ʍs��쐬
Matrix4 CreateMatIdentity();

/// �X�P�[�����O�s��̍쐬
Matrix4 CreateMatScale(Vector3 scale);

/// Z���̉�]�s��쐬
Matrix4 CreateMatRotationZ(Vector3 rotation);

/// X���̉�]�s��쐬
Matrix4 CreateMatRotationX(Vector3 rotation);


/// Y���̉�]�s��
Matrix4 CreateMatRotationY(Vector3 rotation);


/// ���s�ړ�
Matrix4 CreateMatTranslation(Vector3 translation);