#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ObjectsManager.h"

void SceneManager::Init()
{
	// �V�[���̓o�^
	AddScene(new TitleScene());
	AddScene(new GameScene());

	// �V�[���̏�����
	m_pNowScene = m_Scenes["TitleScene"];
	m_pNowScene->Init();

	// �t�F�[�h�̏�����
	m_pFade = OBJECTS_MANAGER.AddObject<Fade>();
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
	// �t�F�[�h�̉��
	if (m_pFade) { m_pFade->Destroy(); }
}

void SceneManager::Update()
{
	// �t�F�[�h���̓V�[�����X�V���Ȃ�
	if (m_pFade->IsFade()) { return; }

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
	// �t�F�[�h���̓V�[����ς���Ȃ�
	if (m_pFade->IsFade()) { return; }

	// �t�F�[�h�̊J�n
	m_pFade->FadeIn(1.0f);

	// �V�[���̕ύX
	m_pNowScene->Uninit();
	m_pNowScene = m_Scenes[name];
	m_pNowScene->Init();

}
