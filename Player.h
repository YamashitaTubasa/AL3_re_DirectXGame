#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include "ViewProjection.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include <memory>
#include <list>

/// <summary>
/// 自キャラ
/// </summary>
class Player
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name = "model">モデル</param>
	/// <param mame = "textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model,uint32_t textureHandle);

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
	/// 攻撃
	/// </summary>
	void Attack();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	// 弾リストを取得
	const std::list < std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }

	float GetRadius();

	void SetParent(WorldTransform* worldTransform);

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
	// 弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	// 半径
	const float radius_ = 1.0f;
	// デスフラグ
	bool isDead_ = false;
};
