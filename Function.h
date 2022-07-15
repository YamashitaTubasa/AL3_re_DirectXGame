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

