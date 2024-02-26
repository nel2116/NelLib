#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "ObjectsManager.h"

void SceneManager::Init()
{
	// �V�[���̓o�^
	AddScene(NEW TitleScene());
	AddScene(NEW GameScene());

	// �t�F�[�h�̏�����
	m_pFade = OBJECTS_MANAGER.AddObject<Fade>();

	// �V�[���̏�����
	m_pNextScene = m_pNowScene = m_Scenes["TitleScene"];
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
	// �t�F�[�h�̉��
	if (m_pFade) { m_pFade->Destroy(); }
}

void SceneManager::Update()
{
	if (m_pNextScene != m_pNowScene)
	{
		if (m_pFade->GetState() != Fade::FADE_OUT)
		{
			// �t�F�[�h�̏I��
			m_pFade->FadeIn(1.0f);

			// ���݂̃V�[���̏I��
			if (m_pNowScene) { m_pNowScene->Uninit(); }

			// ���̃V�[���̊J�n
			m_pNowScene = m_pNextScene;
			m_pNowScene->Init();
		}
	}

	// ���݂̃V�[���̍X�V
	// �t�F�[�h���͍X�V���Ȃ�
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
	// �V�[���̒ǉ�
	m_Scenes[pScene->GetName()] = pScene;
}

void SceneManager::ChangeScene(const std::string& name)
{
	// �t�F�[�h���̓V�[����ς���Ȃ�
	if (m_pFade->IsFade()) { return; }

	// �t�F�[�h�̊J�n
	m_pFade->FadeOut(1.0f);

	// �V�[���̕ύX
	m_pNextScene = m_Scenes[name];
}

void SceneManager::ResetScene()
{
	// �t�F�[�h���̓V�[�������Z�b�g�ł��Ȃ�
	if (m_pFade->IsFade()) { return; }

	// �t�F�[�h�̊J�n
	m_pFade->FadeIn(1.0f);

	// �V�[���̃��Z�b�g
	m_pNowScene->Uninit();
	m_pNowScene->Init();
}
