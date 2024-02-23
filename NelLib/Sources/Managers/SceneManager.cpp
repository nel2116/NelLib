#include "SceneManager.h"
#include <System/Scenes/TitleScene.h>
#include <System/Scenes/GameScene.h>

void SceneManager::Init()
{
	// �V�[���̓o�^
	AddScene(new TitleScene());
	AddScene(new GameScene());

	// �V�[���̏�����
	for (auto& scene : m_Scenes)
	{
		scene.second->Init();
	}
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
	// ���݂̃V�[�����Ȃ��ꍇ�͒ǉ������V�[�������݂̃V�[���ɂ���
	if (m_pNowScene == nullptr)
	{
		m_pNowScene = pScene;
	}
}

void SceneManager::ChangeScene(const std::string& name)
{
	// �V�[���̕ύX
	m_pNowScene = m_Scenes[name];
}
