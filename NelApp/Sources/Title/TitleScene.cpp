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
	// �V�[���̖��O��ݒ�
	m_name = "TitleScene";
}

void TitleScene::Init()
{
	// �V�[���̏�����
	CAMERA_MANAGER.SetNowCamera(CameraManager::E_CAM_DEBUG);
	m_TitleUI = OBJECTS_MANAGER.AddObjects<TitleUI>();
	m_TitleBackGround = OBJECTS_MANAGER.AddObjects<TitleBackGround>();
}

void TitleScene::Uninit()
{
	// �V�[���̏I��
	if (m_TitleUI) { m_TitleUI->Destroy(); }
	if (m_TitleBackGround) { m_TitleBackGround->Destroy(); }
}

void TitleScene::Update()
{
	if (IsKeyPress(VK_RETURN))
	{
		// �V�[���̕ύX
		SCENE_MANAGER.ChangeScene("GameScene");
	}
}

void TitleScene::Draw()
{
}
