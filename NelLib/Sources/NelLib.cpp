// ====== インクルード部 ======
#include<crtdbg.h>
#include <DirectX/Renderer.h>
#include <DirectX/Sprite.h>
#include <NelLib.h>
#include <Managers/ObjectsManager.h>
#include <Managers/SceneManager.h>
#include <Managers/TimeManger.h>
#include <Managers/CameraManager.h>
#include <Managers/TextureManager.h>
#include <Managers/ModelManager.h>

// ====== プロトタイプ宣言 ======
void Init();
void Uninit();
void Input();
void Update();
void Draw();

void window(const char* appName, int width, int height)
{
	// 各初期化
	createWindow(appName, width, height);
	RENDERER.Init(width, height, false);
	Geometory::Init();					// ジオメトリ初期化
	Sprite::Init();						// スプライト初期化
	InitInput();						// 入力初期化
	// マネージャ初期化
	MODEL_MANAGER.Init();				// モデルマネージャ初期化
	OBJECTS_MANAGER.Init();				// オブジェクトマネージャ初期化
	SCENE_MANAGER.Init();				// シーンマネージャ初期化
	TEXTURE_MANAGER.Init();				// テクスチャマネージャ初期化
	TIME_MANAGER.Init();				// タイムマネージャ初期化
	CAMERA_MANAGER.Init();				// カメラマネージャ初期化

	// ジオメトリ用カメラ初期化
	DirectX::XMFLOAT4X4 mat[2];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(1.5f, 2.5f, -3.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
		)));
	DirectX::XMStoreFloat4x4(&mat[1], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(60.0f), (float)width / height, 0.1f, 100.0f)
	));
	Geometory::SetView(mat[0]);
	Geometory::SetProjection(mat[1]);
}

void DrawGrid()
{
	// グリッド
	DirectX::XMFLOAT4 lineColor(0.5f, 0.5f, 0.5f, 1.0f);
	float size = DEBUG_GRID_NUM * DEBUG_GRID_MARGIN;
	for (int i = 1; i <= DEBUG_GRID_NUM; ++i)
	{
		float grid = i * DEBUG_GRID_MARGIN;
		DirectX::XMFLOAT3 pos[2] = {
			DirectX::XMFLOAT3(grid, 0.0f, size),
			DirectX::XMFLOAT3(grid, 0.0f,-size),
		};
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = pos[1].x = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].x = size;
		pos[1].x = -size;
		pos[0].z = pos[1].z = grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
		pos[0].z = pos[1].z = -grid;
		Geometory::AddLine(pos[0], pos[1], lineColor);
	}
	// 軸
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(size, 0, 0), DirectX::XMFLOAT4(1, 0, 0, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, size, 0), DirectX::XMFLOAT4(0, 1, 0, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, size), DirectX::XMFLOAT4(0, 0, 1, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(-size, 0, 0), DirectX::XMFLOAT4(0, 0, 0, 1));
	Geometory::AddLine(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, -size), DirectX::XMFLOAT4(0, 0, 0, 1));

	Geometory::DrawLines();
}

void gmain()
{
	Init();
	while (!quit())
	{
		// タイムマネージャ更新
		TIME_MANAGER.Update();
		// 入力情報の更新
		UpdateInput();
		// ウィンドウが閉じられたら終了
		if (escKeyPressed()) { closeWindow(); }

		if (TIME_MANAGER.GetDeltaTimeSecond() >= 1.0f / 60)
		{
			// 以下にゲームの処理を書く
			// ===== 入力処理 =====
			Input();
			// ===== 更新処理 =====
			SCENE_MANAGER.Update();
			Update();
			// ===== 描画処理 =====

			// ===== 描画処理 =====
			RENDERER.Begin();	// 描画開始

			Draw();

			RENDERER.End();		// 描画終了

			// 最終実行時間の更新
			TIME_MANAGER.UpdateLastTime();
		}
	}
	Uninit();
}

int APIENTRY WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ INT)
{
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ゲームのメインループ
	gmain();

	// システムの終了処理
	UninitInput();
	Sprite::Uninit();
	Geometory::Uninit();
	RENDERER.Release();
	return 0;
}