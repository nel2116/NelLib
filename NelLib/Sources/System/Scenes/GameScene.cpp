#include "GameScene.h"
#include <Managers/SceneManager.h>

void GameScene::Init()
{
	// �V�[���̖��O��ݒ�
	m_name = "GameScene";

	// �V�[���̏�����
	ShowName();
}

void GameScene::Uninit()
{
}

void GameScene::Update()
{
	if (VK_RETURN)
	{
		// �V�[���̕ύX
		SCENE_MANAGER.ChangeScene("TitleScene");
	}
}

void GameScene::Draw()
{
}
