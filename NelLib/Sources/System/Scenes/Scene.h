#pragma once
// ====== �C���N���[�h ======
#include <string>
#include <Windows.h>

// ====== �N���X�̐錾 ======
class Scene
{
public:
	Scene() {}
	~Scene() {}

	// ������
	virtual void Init() = 0;
	// �I��
	virtual void Uninit() = 0;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw() = 0;

	// �V�[���̖��O���擾
	std::string GetName() { return m_name; }
	// �V�[���̖��O��ݒ�
	void SetName(const std::string& name) { m_name = name; }

	// �V�[�����̕\��
	void ShowName();

protected:
	// �V�[���̖��O
	std::string m_name;

};