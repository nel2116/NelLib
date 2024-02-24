#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"

void SceneManager::Init()
{
	// シーンの登録
	AddScene(new TitleScene());
	AddScene(new GameScene());

	// シーンの初期化
	m_pNowScene = m_Scenes.begin()->second;
	m_pNowScene->Init();
}

void SceneManager::Uninit()
{
	// シーンの解放
	for (auto scene : m_Scenes)
	{
		scene.second->Uninit();
		SAFE_DELETE(scene.second);
	}
	// マップのクリア
	m_Scenes.clear();
}

void SceneManager::Update()
{
	// 現在のシーンの更新
	if (m_pNowScene)
	{
		m_pNowScene->Update();
	}
}

void SceneManager::Draw()
{
}

void SceneManager::AddScene(Scene* pScene)
{
	// シーンの追加
	m_Scenes[pScene->GetName()] = pScene;
}

void SceneManager::ChangeScene(const std::string& name)
{
	// シーンの変更
	m_pNowScene->Uninit();
	m_pNowScene = m_Scenes[name];
	m_pNowScene->Init();
}
