#include "GameScene.h"
#include <Managers/SceneManager.h>

void GameScene::Init()
{
	// シーンの名前を設定
	m_name = "GameScene";

	// シーンの初期化
	ShowName();
}

void GameScene::Uninit()
{
}

void GameScene::Update()
{
	if (VK_RETURN)
	{
		// シーンの変更
		SCENE_MANAGER.ChangeScene("TitleScene");
	}
}

void GameScene::Draw()
{
}
