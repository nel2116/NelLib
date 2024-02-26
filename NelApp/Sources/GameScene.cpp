#include "GameScene.h"
#include <Managers/SceneManager.h>
#include <Managers/ObjectsManager.h>
#include <Managers/CameraManager.h>
#include <System/Input.h>

GameScene::GameScene()
	: m_Field(nullptr)
	, m_Player(nullptr)
{
	// シーンの名前を設定
	m_name = "GameScene";
}

void GameScene::Init()
{
	// カメラの設定
	CAMERA_MANAGER.SetNowCamera(CameraManager::E_CAM_PLAYER);
	m_Field = OBJECTS_MANAGER.AddObject<Field>();
	m_Player = OBJECTS_MANAGER.AddObject<Player>();
}

void GameScene::Uninit()
{
	if (m_Player) { m_Player->Destroy(); }
	if (m_Field) { m_Field->Destroy(); }
}

void GameScene::Update()
{
	if (IsKeyPress(VK_RETURN))
	{
		// シーンの変更
		SCENE_MANAGER.ChangeScene("TitleScene");
	}
}

void GameScene::Draw()
{
}
