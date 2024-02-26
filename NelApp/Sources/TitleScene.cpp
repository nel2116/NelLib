#include "TitleScene.h"
#include <Managers/SceneManager.h>
#include <Managers/CameraManager.h>
#include <Managers/ObjectsManager.h>
#include <System/Input.h>

TitleScene::TitleScene()
{
	// �V�[���̖��O��ݒ�
	m_name = "TitleScene";
}

void TitleScene::Init()
{
	// �V�[���̏�����
	CAMERA_MANAGER.SetNowCamera(CameraManager::E_CAM_DEBUG);
	m_TitleUI = OBJECTS_MANAGER.AddObject<TitleUI>();
}

void TitleScene::Uninit()
{
	// �V�[���̏I��
	if (m_TitleUI) { m_TitleUI->Destroy(); }
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
