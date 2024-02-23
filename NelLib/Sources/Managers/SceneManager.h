#pragma once
// ====== �C���N���[�h ======
#include <map>
#include <System/Singleton.h>
#include <System/Scenes/Scene.h>

// ====== �N���X�̐錾 ======

class SceneManager : public Singleton<SceneManager>
{
public:
	// �f�X�g���N�^
	~SceneManager() { Uninit(); }

	void Init();	// ����������
	void Uninit();	// �I������
	void Update();	// �X�V����
	void Draw();	// �`�揈��

	// �V�[���̒ǉ�
	void AddScene(Scene* pScene);
	// �V�[�����ŃV�[����ύX
	void ChangeScene(const std::string& name);
	// �V�[���̎擾
	Scene* GetScene() { return m_pNowScene; }
	// �V�[��������V�[���̎擾
	Scene* GetScene(const std::string& name) { return m_Scenes[name]; }
	// �V�[�����̎擾
	std::string GetSceneName() { return m_pNowScene->GetName(); }


private:	// �����o�ϐ�
	Scene* m_pNowScene;	// ���݂̃V�[��
	std::map<std::string, Scene*> m_Scenes;	// �V�[���̃��X�g


private:	// �V���O���g���֘A
	friend Singleton<SceneManager>;
	SceneManager() : m_pNowScene(nullptr) {}
};
// �V�[���}�l�[�W���̃C���X�^���X�̎擾
#define SCENE_MANAGER SceneManager::GetInstance()