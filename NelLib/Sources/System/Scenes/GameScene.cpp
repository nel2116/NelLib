#include "GameScene.h"
#include <Managers/SceneManager.h>
#include <System/Input.h>

GameScene::GameScene()
{
	// �V�[���̖��O��ݒ�
	m_name = "GameScene";
}

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
	if (IsKeyPress(VK_RETURN))
	{
		// �V�[���̕ύX
		SCENE_MANAGER.ChangeScene("TitleScene");
	}
}

void GameScene::Draw()
{
}
