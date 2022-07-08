﻿#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "AxisIndicator.h"
#include "Player.h"
#include "Enemy.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	//ワールドトランスフォーム
	/*WorldTransform worldTransforms_[100];*/

	//カメラ上方向の角度
	float viewAngle = 4.0f;

	//パーツID
	enum Partid {
		kRoot,    // 大本
		kSpine,	  // 脊髄
		kChest,	  // 胸
		kHead,	  // 頭
		kArmL,	  // 左腕
		kArmR,	  // 右腕
		kHip,	  // 尻
		kLegL,	  // 左足
		kLegR,	  // 右足

		kNumPartid
	};
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	float Angle(float angle);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	//3Dモデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 自キャラ
	Player* player_ = nullptr;
	// 敵キャラ
	Enemy* enemy_ = nullptr;
	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};