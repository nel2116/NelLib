#include "TitleScene.h"
#include <Managers/SceneManager.h>
#include <Managers/CameraManager.h>
#include <Managers/ObjectsManager.h>
#include <Managers/TextureManager.h>
#include <System/Input.h>
#include <DirectX/Sprite.h>

TitleScene::TitleScene()
	: m_TitleUI(nullptr)
{
	// シーンの名前を設定
	m_name = "TitleScene";
}

void TitleScene::Init()
{
	// シーンの初期化
	CAMERA_MANAGER.SetNowCamera(CameraManager::E_CAM_DEBUG);
	m_TitleUI = OBJECTS_MANAGER.AddObjects<TitleUI>();
	m_TitleBackGround = OBJECTS_MANAGER.AddObjects<TitleBackGround>();
}

void TitleScene::Uninit()
{
	// シーンの終了
	if (m_TitleUI) { m_TitleUI->Destroy(); }
	if (m_TitleBackGround) { m_TitleBackGround->Destroy(); }
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
