#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"

void SceneManager::Init()
{
	// �V�[���̓o�^
	AddScene(new TitleScene());
	AddScene(new GameScene());

	// �V�[���̏�����
	m_pNowScene = m_Scenes.begin()->second;
	m_pNowScene->Init();
}

void SceneManager::Uninit()
{
	// �V�[���̉��
	for (auto scene : m_Scenes)
	{
		scene.second->Uninit();
		SAFE_DELETE(scene.second);
	}
	// �}�b�v�̃N���A
	m_Scenes.clear();
}

void SceneManager::Update()
{
	// ���݂̃V�[���̍X�V
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
	// �V�[���̒ǉ�
	m_Scenes[pScene->GetName()] = pScene;
}

void SceneManager::ChangeScene(const std::string& name)
{
	// �V�[���̕ύX
	m_pNowScene->Uninit();
	m_pNowScene = m_Scenes[name];
	m_pNowScene->Init();
}
