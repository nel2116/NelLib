#pragma once
// ====== �C���N���[�h�� ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>

// ====== �N���X�錾 ======
class Fade : public Object
{
public:
	// �t�F�[�h�̏��
	enum FADE_STATE
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT
	};

public:
	// �R���X�g���N�^
	Fade();
	// �f�X�g���N�^
	~Fade();

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

	// �t�F�[�h�C��
	void FadeIn(float time);

	// �t�F�[�h�A�E�g
	void FadeOut(float time);

	// �t�F�[�h�����ǂ���
	// true : �t�F�[�h��
	// false : �t�F�[�h���łȂ�
	bool IsFade() { return m_FadeState != FADE_NONE; }

	// �t�F�[�h�̏�Ԃ��擾
	FADE_STATE GetState() { return m_FadeState; }

private:
	// �t�F�[�h�̏��
	FADE_STATE m_FadeState;

	// �t�F�[�h�̎���
	float m_fFadeTime;

	// �t�F�[�h�̎��ԃJ�E���g
	float m_fFadeTimeCount;

	// �A���t�@�l
	float m_fAlpha;

	// �t�F�[�h�̃e�N�X�`��
	SpriteComponent* m_pSprite;
};