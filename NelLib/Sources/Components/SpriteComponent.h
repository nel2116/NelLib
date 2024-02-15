#pragma once

// ====== �C���N���[�h�� ======
#include <DirectX/Texture.h>
#include <Components/Component.h>

// ====== �N���X�̐錾 ======
class SpriteComponent : public Component
{

public:
	// �R���X�g���N�^
	SpriteComponent(class Object* owner) : Component(owner), m_pTex(nullptr) {}
	// �f�X�g���N�^
	~SpriteComponent() {}

	// ������
	void Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �e�N�X�`���̐ݒ�
	void SetTexture(Texture* tex) { m_pTex = tex; }

private:
	// �e�N�X�`��
	Texture* m_pTex;
};