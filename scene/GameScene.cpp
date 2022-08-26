#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "Function.h"
#include <random>

#define PI 3.14

float GameScene::Angle(float angle)
{
	return (float)angle * PI / 180;
}

float Degree(const float& degree) {
	float n = (float)degree * PI / 180;
	return n;
}

void GameScene::CheckAllCollisions() {
	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets)
	{
		// 敵弾の座標
		posB = bullet->GetWorldPosition();

		// 座標AとBの距離を求める
		Vector3 len = Vector3sub(posA, posB);
		float distance = length(len);

		// 自キャラと敵弾の半径
		float radius = player_->GetRadius() + bullet->GetRadius();

		// 自キャラと敵弾の交差判定
		if (distance <= radius) {
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	// 敵キャラの座標
	posA = enemy_->GetWorldPosition();

	// 自弾と敵キャラ全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		// 敵弾の座標
		posB = bullet->GetWorldPosition();
		// AとBの距離を求める
		Vector3 len = Vector3sub(posA, posB);
		float distance = length(len);

		// 自弾と敵キャラの半径
		float radius = enemy_->GetRadius() + bullet->GetRadius();

		// 自弾と敵キャラの交差判定
		if (distance <= radius) {
			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	// 自弾と敵弾全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bulletA : playerBullets) {
		for (const std::unique_ptr<EnemyBullet>& bulletB : enemyBullets) {

			// 自弾の座標
			posB = bulletA->GetWorldPosition();
			// 敵弾の座標
			posA = bulletB->GetWorldPosition();

			Vector3 len = Vector3sub(posA, posB);
			// 座標AとBの距離を求める
			float distance = length(len);

			// 自弾と敵弾の半径
			float radius = bulletB->GetRadius() + bulletA->GetRadius();

			// 自弾と敵弾の交差判定
			if (distance <= radius) {
				bulletB->OnCollision();
				bulletA->OnCollision();
			}
		}
	}
#pragma endregion
}


//乱数シード生成器
std::random_device seed_gen;
//メルセンヌ・ツイスターの乱数エンジン
std::mt19937_64 engine(seed_gen());
//乱数範囲の指定
std::uniform_real_distribution<float> posDist(-10.0f, 10.0f);
std::uniform_real_distribution<float> rotDist(0.0f, 3.14f);

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
	delete player_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	//3Dモデルの生成
	model_ = Model::Create();

	// 自キャラの生成
	player_ = new Player();

	// 自キャラの初期化
	player_->Initialize(model_, textureHandle_);

	// 敵キャラの生成
	enemy_ = new Enemy();

	// 敵キャラの初期化
	enemy_->Initialize(model_, textureHandle_);

	// 敵キャラに時期キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	// 3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	
	// 天球の生成
	skydome_ = new Skydome();

	// 背景
	skydome_->Initialize(modelSkydome_);

	// レールカメラ生成
	railCamera_ = new RailCamera();

	// レールカメラ初期化
	railCamera_->Initialize();

	////カメラ視点座標を設定
	//viewProjection_.eye = { 0,0,-10 };

	////カメラ注視点座標を設定
	//viewProjection_.target = { 10,0,0 };

	////カメラ上方向ベクトルを設定(右上45度指定)
	//viewProjection_.up = { cosf(3.14f / 4.0f),sinf(3.14f / 4.0f),0.0f };

	//カメラ垂直方向視野角を設定
	//viewProjection_.fovAngleY = 3.14f / 18.0f;

	////アスペクトル比を設定
	//viewProjection_.aspectRatio = 1.0f;

	////ニアクリップ距離を設定
	//viewProjection_.nearZ = 52.0f;
	////ファークリップ距離を設定
	//viewProjection_.farZ = 53.0f;

	//ビュープロジェクション
	viewProjection_.Initialize();

	//デバックカメラの生成
	/*debugCamera_ = new DebugCamera(600, 400);*/

	//軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);

	//軸方向が参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	//Matrix4 matIdentity;
	//matIdentity.m[0][0] = 1;
	//matIdentity.m[1][1] = 1;
	//matIdentity.m[2][2] = 1;
	//matIdentity.m[3][3] = 1;

	///*{
	//	1,0,0,0
	//	0,1,0,0
	//	0,0,1,0
	//	0,0,0,1
	//}*/

}

void GameScene::Update() {
	//デバックカメラの更新
	/*debugCamera_->Update();*/

	// 自キャラの更新
	player_->Update();

	// 敵キャラの更新
	enemy_->Update();

	CheckAllCollisions();

	// 背景の更新
	skydome_->Update();

	// レールカメラ更新
	railCamera_->Update();

	////-------クリップ距離変更処理-------////
	//{
	//	//上下キーニアクリップ距離を増減
	//	if (input_->PushKey(DIK_UP)) {
	//		viewProjection_.nearZ += 0.1f;
	//	}
	//	else if (input_->PushKey(DIK_DOWN)) {
	//		viewProjection_.nearZ -= 0.1f;
	//	}

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	//デバック用表示
	//	debugText_->SetPos(50, 130);
	//	debugText_->Printf("nearZ : %f", viewProjection_.nearZ);
	//}


	////--------Fov変更処理-------//
	//{
	//	//上キーで視野角を広げる
	//	if (input_->PushKey(DIK_UP)) {
	//		viewProjection_.fovAngleY += 0.01f;
	//		if (viewProjection_.fovAngleY >= 3.14f) {
	//			viewProjection_.fovAngleY = 3.14f;
	//		}
	//	}
	//	else if(input_->PushKey(DIK_DOWN)) {
	//		viewProjection_.fovAngleY -= 0.01f;
	//		if (viewProjection_.fovAngleY <= 0.01f) {
	//			viewProjection_.fovAngleY = 0.01f;
	//		}
	//	}

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	//デバック用表示
	//	debugText_->SetPos(50, 110);
	//	debugText_->Printf("fovAngleY(Degree):%f",180 / 3.14f *(viewProjection_.fovAngleY));
	//}

	////-------視点移動処理-------//
	//{

	//	Vector3 cameramove = Vector3();

	//	//視点の移動の速さ
	//	const float kEyeSpeed = 0.2f;

	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_W)) {
	//		cameramove.z += kEyeSpeed;
	//	}
	//	else if (input_->PushKey(DIK_S)) {
	//		cameramove.z -= kEyeSpeed;
	//	}

	//	//視点移動(ベクトルの加算)
	//	viewProjection_.eye += cameramove;
	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	//デバック用表示
	//	debugText_->SetPos(50, 50);
	//	debugText_->Printf("eye:(%f,%f,%f)",
	//					   viewProjection_.eye.x,
	//					   viewProjection_.eye.y,
	//					   viewProjection_.eye.z);
	//}

	////-------注視点移動処理-------//
	//{

	//	Vector3 targetmove = Vector3();

	//	//注視点の移動速さ
	//	const float kTargetSpeed = 0.2f;

	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_LEFT)) {
	//		targetmove.x -= kTargetSpeed;
	//	}
	//	else if (input_->PushKey(DIK_RIGHT)) {
	//		targetmove.x += kTargetSpeed;
	//	}
	//	//注視点移動(ベクトルの加算)
	//	viewProjection_.target += targetmove;

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	//デバック用表示
	//	debugText_->SetPos(50, 70);
	//	debugText_->Printf("target:(%f,%f,%f)",
	//					   viewProjection_.target.x,
	//					   viewProjection_.target.y,
	//					   viewProjection_.target.z);
	//}

	////-------上方向回転処理-------//
	//{
	//	//上方向の回転の速さ[ラジアン/frame]
	//	const float kUpRotSpeed = 0.05f;

	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_SPACE)) {
	//		viewAngle += kUpRotSpeed;
	//		//2πを超えたら0に戻す
	//		viewAngle = fmodf(viewAngle, 3.14f * 2.0f);
	//	}

	//	//上方向ベクトルを計算(半径1の円周上の座標)
	//	viewProjection_.up = { cosf(viewAngle),sinf(viewAngle),0.0f };

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	//デバック用表示
	//	debugText_->SetPos(50, 90);
	//	debugText_->Printf("up:(%f,%f,%f)",
	//					   viewProjection_.up.x,
	//					   viewProjection_.up.y,
	//					   viewProjection_.up.z);
	//}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>



	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	
	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 敵キャラの描画
	enemy_->Draw(viewProjection_);

	// 背景の描画
	skydome_->Draw(viewProjection_);
	
	////3Dモデル
	//model_->Draw(worldTransforms_[100], viewProjection_, textureHandle_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}