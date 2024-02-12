#include "NelLib.h"
#include <DirectX/Renderer.h>
#include <Managers/ObjectsManager.h>
#include "GameObjects/testObject.h"
#include <Objects/Camera/CameraDebug.h>

TestObject* g_pTestObject = nullptr;

void Init()
{
	// ===== 初期化処理 =====
	window("Nel Game", 960, 540);
	TestObject* test = OBJECTS_MANAGER.AddObject<TestObject>();
	CameraDebug* camera = OBJECTS_MANAGER.AddObject<CameraDebug>();
	test->SetCamera(camera);

}

void Input()
{
}

void Update()
{
	// ===== 更新処理 =====
	OBJECTS_MANAGER.Update();
}

void Draw()
{
	// ===== 描画処理 =====
	CameraDebug* camera = OBJECTS_MANAGER.GetObject<CameraDebug>();
	Geometory::SetView(camera->GetTransposedViewMatrix());
	Geometory::SetProjection(camera->GetTransposedProjectionMatrix());
#if _DEBUG
	DrawGrid();		// グリッド線の描画
#endif // _DEBUG

	OBJECTS_MANAGER.Draw();
}

void Uninit()
{
}