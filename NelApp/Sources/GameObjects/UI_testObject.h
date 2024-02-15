#pragma once

// ====== �C���N���[�h�� ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>

// ====== �N���X�̐錾 ======
class UI_TestObject : public Object
{
public:
	// �R���X�g���N�^
	UI_TestObject() {}
	// �f�X�g���N�^
	~UI_TestObject() {}

	// ������
	void Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �X�v���C�g�R���|�[�l���g
	SpriteComponent* m_pSprite;
};