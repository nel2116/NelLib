#pragma once
// ====== �C���N���[�h�� ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>

// ====== �N���X�錾 ======
class TitleUI : public Object
{
public:
	// �R���X�g���N�^
	TitleUI();
	// �f�X�g���N�^
	~TitleUI();

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

private:
	// ====== �����o�ϐ� ======
	SpriteComponent* m_pSprite;

};