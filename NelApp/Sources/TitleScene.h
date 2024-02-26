#pragma once
// ====== �C���N���[�h ======
#include <System/Scenes/Scene.h>
#include <TitleUI.h>

// ====== �N���X�̐錾 ======
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene() {}

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

private:
	// �V�[���̖��O
	TitleUI* m_TitleUI;
};