#pragma once

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
#include "EnemyBullet.h"
#include "Skydome.h"
#include "RailCamera.h"
#include "Function.h"
#include "ClearScene.h"
#include "StartScene.h"
#include <sstream>
#include "Obstacle.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene 
{
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	//ワールドトランスフォーム
	/*WorldTransform worldTransforms_[100];*/

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

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

	/// <summary>
	/// 敵弾を追加
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet);

	float Angle(float angle);

	// 弾リストを取得
	/*const std::list < std::unique_ptr<Enemy>>& GetEnemy() { return enemy1_; }*/

	/// <summary>
	/// 障害物発生データの読み込み
	/// </summary>
	void LoadObstaclePopData();

	/// <summary>
	/// 障害物発生コマンドの更新
	/// </summary>
	void UpdateObstaclePopCommands();

	/// <summary>
	/// 障害物
	/// </summary>
	void Obstacle(Vector3 Obstacle);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	// 入力処理するため
	Input* input_ = nullptr;
	// 音楽
	Audio* audio_ = nullptr;
	// デバックテキスト
	DebugText* debugText_ = nullptr;
	// ワールド変換データ
	WorldTransform worldTransform_;
	//3Dモデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t textureHandle1_ = 0;
	uint32_t textureHandle2_ = 0;
	uint32_t textureHandle3_ = 0;
	// サウンドデータハンドル
	uint32_t soundDateHandle_ = 0;
	// 音声再生ハンドル
	uint32_t voiceHandle_ = 0;
	// 自キャラ
	Player* player_ = nullptr;
	// 敵キャラ
	Enemy* enemy_ = nullptr;
	// 自弾
	PlayerBullet* playerBullet_ = nullptr;
	// 敵弾
	EnemyBullet* enemyBullet_ = nullptr;
	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	// 背景
	Skydome* skydome_ = nullptr;
	// 3Dモデル
	Model* modelSkydome_ = nullptr;
	// レールカメラ
	RailCamera* railCamera_ = nullptr;
	//std::unique_ptr<RailCamera> railCamera_;
	// 敵弾
	/*std::list<std::unique_ptr<Enemy>> enemy1_;*/
	// クリアシーン
	ClearScene* clearScene_ = nullptr;
	// クリアシーンフラグ
	int clearSceneFlag = 0;
	// スタートシーン
	StartScene* startScene_ = nullptr;
	// スタートシーンフラグ
	int startSceneFlag = 0;
	// カメラ上方向の角度
	float viewAngle = 4.0f;
	// レールカメラタイマー
	float railCameraTimer = 0;
	// 障害物発生コマンド
	std::stringstream obstaclePopCommands;
	bool isWait_ = false;
	int waitTimer = 100;

};