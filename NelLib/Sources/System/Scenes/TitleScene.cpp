#include "TitleScene.h"
#include <Managers/SceneManager.h>
#include <System/Input.h>

TitleScene::TitleScene()
{
	// �V�[���̖��O��ݒ�
	m_name = "TitleScene";
}

void TitleScene::Init()
{
	// �V�[���̏�����
	ShowName();
}

void TitleScene::Uninit()
{
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
