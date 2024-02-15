#include "NelLib.h"
#include <DirectX/Renderer.h>
#include <Managers/ObjectsManager.h>
#include <Managers/CameraManager.h>
#include "GameObjects/testObject.h"
#include "GameObjects/UI_testObject.h"

void Init()
{
	// ===== 初期化処理 =====
	window("Nel Game", 960, 540);
	OBJECTS_MANAGER.AddObject<TestObject>();
//	UI_TestObject* UI = OBJECTS_MANAGER.AddObject<UI_TestObject>();
	//UI->SetOrder(100);
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
	CameraBase* camera = CAMERA_MANAGER.GetNowCamera();
	Geometory::SetView(camera->GetTransposedViewMatrix());
	Geometory::SetProjection(camera->GetTransposedProjectionMatrix());

#if _DEBUG	// デバッグ時のみ
	DrawGrid();		// グリッド線の描画
#endif // _DEBUG

	OBJECTS_MANAGER.Draw();
}

void Uninit()
{
}