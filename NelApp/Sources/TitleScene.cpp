#include "TitleScene.h"
#include <Managers/SceneManager.h>
#include <Managers/CameraManager.h>
#include <Managers/ObjectsManager.h>
#include <System/Input.h>

TitleScene::TitleScene()
{
	// シーンの名前を設定
	m_name = "TitleScene";
}

void TitleScene::Init()
{
	// シーンの初期化
	CAMERA_MANAGER.SetNowCamera(CameraManager::E_CAM_DEBUG);
	m_TitleUI = OBJECTS_MANAGER.AddObject<TitleUI>();
}

void TitleScene::Uninit()
{
	// シーンの終了
	if (m_TitleUI) { m_TitleUI->Destroy(); }
}

void TitleScene::Update()
{
	if (IsKeyPress(VK_RETURN))
	{
		// シーンの変更
		SCENE_MANAGER.ChangeScene("GameScene");
	}
}

void TitleScene::Draw()
{

}
