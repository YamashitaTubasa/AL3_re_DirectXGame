#pragma once

#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include "ViewProjection.h"
#include "Function.h"
#include <memory>
#include <list>
#include <cassert>

/// <summary>
/// 天球
/// </summary>
class Skydome
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize(Model* model);

    /// <summary>
    /// 更新
    /// </summary>
    void Update();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(ViewProjection viewProjection);
    
private:
    // ワールド変換データ
    WorldTransform worldTransform_;
    // モデル
    Model* model_ = nullptr;
    //
    Input* input_ = nullptr;
};
