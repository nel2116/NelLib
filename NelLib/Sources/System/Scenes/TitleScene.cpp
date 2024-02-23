#include "TitleScene.h"
#include <System/Input.h>
#include <Managers/SceneManager.h>

void TitleScene::Init()
{
	// �V�[���̖��O��ݒ�
	m_name = "TitleScene";

	// �V�[���̏�����
	ShowName();
}

void TitleScene::Uninit()
{
}

void TitleScene::Update()
{
	if (VK_RETURN)
	{
		// �V�[���̕ύX
		SCENE_MANAGER.ChangeScene("GameScene");
	}
}

void TitleScene::Draw()
{

}
