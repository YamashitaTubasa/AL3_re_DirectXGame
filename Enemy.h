#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include "Player.h"
#include <memory>
#include <list>

// 自機クラスの前方宣言
class Player;
// GameeSceneの前方宣言（苦肉の策）
class GameScene;

class Enemy
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name = "model">モデル</param>
	/// <param mame = "textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjectione">ビュープロジェクション（参照渡し）</param>
	void Draw(ViewProjection viewProjection_);

	/// <summary>
	/// 弾の発射
	/// </summary>
	void Fire();

	// 行動フェーズ
	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
	};

	// 発射間隔
	static const int kFireInterval = 70;

	// 接近フェーズの初期化
	void ApproachInitialize();

	void SetPlayer(Player* player) { player_ = player; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	bool IsDead() const { return isDead_; }

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// 弾リストを取得
	const std::list < std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

	float GetRadius();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 入力処理するため
	Input* input_ = nullptr;
	// デバックテキスト
	DebugText* debugText_ = nullptr;
	// フェーズ
	Phase phase_ = Phase::Approach;
	// 弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	// 接近フェーズの更新
	void AccessPhaseUpdate();
	// 離脱フェーズの更新
	void EliminationPhaseUpdate();
	// 発射タイマー
	int32_t fireTimer = 0;
	// 自キャラ
	Player* player_ = nullptr;
	// 半径
	const float radius_ = 1.0f;
	// デスフラグ
	bool isDead_ = false;
	// ゲームシーン
	GameScene* gameScene_ = nullptr;

};

