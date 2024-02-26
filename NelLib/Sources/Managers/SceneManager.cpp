#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ObjectsManager.h"

void SceneManager::Init()
{
	// シーンの登録
	AddScene(new TitleScene());
	AddScene(new GameScene());

	// シーンの初期化
	m_pNowScene = m_Scenes["TitleScene"];
	m_pNowScene->Init();

	// フェードの初期化
	m_pFade = OBJECTS_MANAGER.AddObject<Fade>();
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
	// フェードの解放
	if (m_pFade) { m_pFade->Destroy(); }
}

void SceneManager::Update()
{
	// フェード中はシーンを更新しない
	if (m_pFade->IsFade()) { return; }

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
	// フェード中はシーンを変えれない
	if (m_pFade->IsFade()) { return; }

	// フェードの開始
	m_pFade->FadeIn(1.0f);

	// シーンの変更
	m_pNowScene->Uninit();
	m_pNowScene = m_Scenes[name];
	m_pNowScene->Init();

}
