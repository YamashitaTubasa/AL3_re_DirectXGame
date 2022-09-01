#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include "Function.h"
#include "Input.h"

/// <summary>
/// レールカメラ
/// </summary>
class RailCamera
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name = "position">初期座標</param>
	/// <param name = "rotation">初期角度</param>
	void Initialize(const Vector3& position, const Vector3& rotation);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 行列
	/// </summary>
	void UpdateMatrix();

	/// <summary>
	/// ビュープロジェクションを取得
	/// </summary>
	/// <returns>ビュープロジェクション</returna>
	const ViewProjection& GetViewProjection() { return viewProjection_; }

	// ワールド行列を取得
	WorldTransform* GetWorldMatrix() { return &worldTransform_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;
	DebugText* debugText_ = nullptr;
	// 入力処理するため
	Input* input_ = nullptr;
};

