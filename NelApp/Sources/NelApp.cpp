#include "NelLib.h"
#include <DirectX/Renderer.h>
#include <Managers/ObjectsManager.h>
#include <Managers/CameraManager.h>
#include <Managers/SceneManager.h>

void Init()
{
	// ===== 初期化処理 =====
	window("Nel Game", 1280, 720);


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
	Geometory::SetView(camera->GetViewMatrix());
	Geometory::SetProjection(camera->GetProjectionMatrix());

#if _DEBUG	// デバッグ時のみ
	DrawGrid();		// グリッド線の描画
#endif // _DEBUG

	OBJECTS_MANAGER.Draw();
}

void Uninit()
{
}