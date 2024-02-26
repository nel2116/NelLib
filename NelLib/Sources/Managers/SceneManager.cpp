#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ObjectsManager.h"

void SceneManager::Init()
{
	// シーンの登録
	AddScene(NEW TitleScene());
	AddScene(NEW GameScene());

	// フェードの初期化
	m_pFade = OBJECTS_MANAGER.AddObject<Fade>();

	// シーンの初期化
	m_pNextScene = m_pNowScene = m_Scenes["TitleScene"];
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
	// フェードの解放
	if (m_pFade) { m_pFade->Destroy(); }
}

void SceneManager::Update()
{
	if (m_pNextScene != m_pNowScene)
	{
		if (m_pFade->GetState() != Fade::FADE_OUT)
		{
			// フェードの終了
			m_pFade->FadeIn(1.0f);

			// 現在のシーンの終了
			if (m_pNowScene) { m_pNowScene->Uninit(); }

			// 次のシーンの開始
			m_pNowScene = m_pNextScene;
			m_pNowScene->Init();
		}
	}

	// 現在のシーンの更新
	// フェード中は更新しない
	if (m_pNowScene && !m_pFade->IsFade())
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
	m_pFade->FadeOut(1.0f);

	// シーンの変更
	m_pNextScene = m_Scenes[name];
}

void SceneManager::ResetScene()
{
	// フェード中はシーンをリセットできない
	if (m_pFade->IsFade()) { return; }

	// フェードの開始
	m_pFade->FadeIn(1.0f);

	// シーンのリセット
	m_pNowScene->Uninit();
	m_pNowScene->Init();
}
