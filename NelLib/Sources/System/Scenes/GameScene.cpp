#include "GameScene.h"
#include <Managers/SceneManager.h>
#include <System/Input.h>

GameScene::GameScene()
{
	// シーンの名前を設定
	m_name = "GameScene";
}

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
	if (IsKeyPress(VK_RETURN))
	{
		// シーンの変更
		SCENE_MANAGER.ChangeScene("TitleScene");
	}
}

void GameScene::Draw()
{
}
