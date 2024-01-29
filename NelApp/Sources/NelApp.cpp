#include "NelLib.h"
#include <DirectX/Renderer.h>
#include "GameObjects/testObject.h"

TestObject* g_pTestObject = nullptr;

void Init()
{
	// ===== 初期化処理 =====
	window("Nel Game", 960, 540);

	// ===== ゲームオブジェクトの初期化 =====
	g_pTestObject = new TestObject();
	g_pTestObject->Init();
}

void Input()
{
	// ===== 入力処理 =====
	UpdateInput();
}

void Update()
{
	// ===== ゲームオブジェクトの更新 =====
	g_pTestObject->Update();
}

void Draw()
{
	RENDERER.Begin();

#if _DEBUG
	DrawGrid();		// グリッド線の描画
#endif // _DEBUG

	// ===== ゲームオブジェクトの描画 =====
	g_pTestObject->Draw();

	RENDERER.End();
}
void Uninit()
{
	// ===== ゲームオブジェクトの終了処理 =====
	g_pTestObject->Uninit();

	// ===== 終了処理 =====
	SAFE_DELETE(g_pTestObject);
}

void gmain()
{
	Init();
	while (!quit())
	{
		if (escKeyPressed()) { closeWindow(); }
		// 以下にゲームの処理を書く
		// ===== 入力処理 =====
		Input();
		// ===== 更新処理 =====
		Update();
		// ===== 描画処理 =====
		Draw();
	}
	Uninit();
}