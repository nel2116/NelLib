#include "TitleScene.h"
#include <System/Input.h>
#include <Managers/SceneManager.h>

void TitleScene::Init()
{
	// シーンの名前を設定
	m_name = "TitleScene";

	// シーンの初期化
	ShowName();
}

void TitleScene::Uninit()
{
}

void TitleScene::Update()
{
	if (VK_RETURN)
	{
		// シーンの変更
		SCENE_MANAGER.ChangeScene("GameScene");
	}
}

void TitleScene::Draw()
{

}
