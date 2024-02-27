#include "GameScene.h"
#include <Managers/SceneManager.h>
#include <Managers/ObjectsManager.h>
#include <Managers/CameraManager.h>
#include <System/Input.h>

GameScene::GameScene()
	: m_Field(nullptr)
	, m_Player(nullptr)
{
	// �V�[���̖��O��ݒ�
	m_name = "GameScene";
}

void GameScene::Init()
{
	// �J�����̐ݒ�
	CAMERA_MANAGER.SetNowCamera(CameraManager::E_CAM_PLAYER);
	m_Field = OBJECTS_MANAGER.AddObjects<Field>();
	m_Player = OBJECTS_MANAGER.AddObjects<Player>();
}

void GameScene::Uninit()
{
	if (m_Player) { m_Player->Destroy(); }
	if (m_Field) { m_Field->Destroy(); }
}

void GameScene::Update()
{
	// �l�񂾂Ƃ��p
	if (IsKeyPress('N') && IsKeyPress('X'))
	{
		SCENE_MANAGER.ChangeScene("TitleScene");
	}

}

void GameScene::Draw()
{
}
