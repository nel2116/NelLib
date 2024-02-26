#pragma once
// ====== �C���N���[�h ======
#include <DirectX/Texture.h>
#include <Objects/Camera/CameraBase.h>
#include <System/Scenes/Scene.h>
#include <Title/TitleUI.h>
#include <Title/TitleBackGround.h>

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
	TitleUI* m_TitleUI;
	TitleBackGround* m_TitleBackGround;
};