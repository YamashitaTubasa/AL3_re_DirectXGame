#pragma once

#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// 自機の弾
/// </summary>
class PlayerBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name = "model">モデル</param>
	/// <param name = "position">初期座標</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <srmmary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name = "viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);


	bool IsDead() const { return isDead_; }

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	
	float GetRadius();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 速度
	Vector3 velocity_;
	// 寿命<frm>
	static const int32_t kLifeTime = 60 * 5;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime;
	// デスフラグ
	bool isDead_ = false;
	// 半径
	const float radius_ = 1.0f;
};

