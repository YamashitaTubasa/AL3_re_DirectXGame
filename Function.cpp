#include "Function.h"
#include "worldTransform.h"
#include <math.h>

/// �P�ʍs��쐬
Matrix4 CreateMatIdentity() {
	Matrix4 mat;
	mat.m[0][0] = 1;
	mat.m[1][1] = 1;
	mat.m[2][2] = 1;
	mat.m[3][3] = 1;
	return mat;
}

/// �X�P�[�����O�s��̍쐬
Matrix4 CreateMatScale(Vector3 scale) {
	Matrix4 mat;
	mat.m[0][0] = scale.x;
	mat.m[1][1] = scale.y;
	mat.m[2][2] = scale.z;
	mat.m[3][3] = 1.0f;

	return mat;
}

/// Z���̉�]�s��쐬
Matrix4 CreateMatRotationZ(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.z);
	mat.m[0][1] = sin(rotation.z);
	mat.m[1][0] = -sin(rotation.z);
	mat.m[1][1] = cos(rotation.z);

	return mat;
}

/// X���̉�]�s��쐬
Matrix4 CreateMatRotationX(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[1][1] = cos(rotation.x);
	mat.m[1][2] = sin(rotation.x);
	mat.m[2][1] = -sin(rotation.x);
	mat.m[2][2] = cos(rotation.x);

	return mat;
}


/// Y���̉�]�s��
Matrix4 CreateMatRotationY(Vector3 rotation) {
	Matrix4 mat = CreateMatIdentity();
	mat.m[0][0] = cos(rotation.y);
	mat.m[0][2] = -sin(rotation.y);
	mat.m[2][0] = sin(rotation.y);
	mat.m[2][2] = cos(rotation.y);

	return mat;
}


/// ���s�ړ�
Matrix4 CreateMatTranslation(Vector3 translation) {
	Matrix4 lat = CreateMatIdentity();
	lat.m[3][0] = translation.x;
	lat.m[3][1] = translation.y;
	lat.m[3][2] = translation.z;
	lat.m[3][3] = 1;

	return lat;
}