#include "worldTransform.h"
#include "Input.h"
#include "Enemy.h"
#include <math.h>

// 単位行列作成
Matrix4 CreateMatIdentity();

// スケーリング行列の作成
Matrix4 CreateMatScale(Vector3 scale);

// Z軸の回転行列作成
Matrix4 CreateMatRotationZ(Vector3 rotation);

// X軸の回転行列作成
Matrix4 CreateMatRotationX(Vector3 rotation);

// Y軸の回転行列
Matrix4 CreateMatRotationY(Vector3 rotation);

// 平行移動
Matrix4 CreateMatTranslation(Vector3 translation);

// ワールドトランスフォームの更新
void CreateMatrixUpdate(WorldTransform& worldTransform_);

// キャラクターの旋回処理
void Rotate(WorldTransform& worldTransform_, Input* input_);

// 速度ベクトルを自機の向きに合わせて回転させる
Vector3 CreateVector(Vector3 velocity, WorldTransform& worldTransform);

// 差分ベクトルを求める
Vector3 Vector3sub(Vector3& v1, Vector3& v2);

// ベクトルの正規化
Vector3 Normalize(Vector3& vec);

float length(Vector3& vec);

Vector3 Vector3TransformNormal(Vector3& velocity, Matrix4& mat);