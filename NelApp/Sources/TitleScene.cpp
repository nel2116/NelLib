#include "TitleScene.h"
#include <Managers/SceneManager.h>
#include <Managers/CameraManager.h>
#include <System/Input.h>

TitleScene::TitleScene()
{
	// シーンの名前を設定
	m_name = "TitleScene";
}

void TitleScene::Init()
{
	// シーンの初期化
	ShowName();
	CAMERA_MANAGER.SetNowCamera(CameraManager::E_CAM_DEBUG);
}

void TitleScene::Uninit()
{
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
