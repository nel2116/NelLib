#pragma once

// ====== �C���N���[�h�� ======
#include <DirectX/Texture.h>
#include <Components/Component.h>
#include <Objects/Camera/CameraUI.h>

// ====== �O���錾 ======
#define NORMAL_TEX_VEC Vector3(6.4f, 3.6f, 1.0f)

// ====== �N���X�̐錾 ======
class SpriteComponent : public Component
{
public:
	struct SpriteInfo
	{
		Texture* texture;
		Vector4 color;
		Vector2 size;
		Vector2 uvOffset;
		Vector2 uvScale;
		int splitX;
		int splitY;

		// �R���X�g���N�^
		SpriteInfo(void)
		{
			texture = nullptr;
			color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
			size = Vector2(1.0f, 1.0f);
			uvOffset = Vector2(0.0f, 0.0f);
			uvScale = Vector2(1.0f, 1.0f);
			splitX = 1;
			splitY = 1;
		}
	};

public:
	// �R���X�g���N�^
	SpriteComponent(Object* pObject);

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
	void SetTexture(Texture* tex) { m_spriteInfo.texture = tex; }

	// �J���[�̐ݒ�
	void SetColor(Vector4 color) { m_spriteInfo.color = color; }

	void SetAlpha(float alpha) { m_spriteInfo.color.w = alpha; }

	// �T�C�Y�̐ݒ�
	void SetSize(Vector2 size) { m_spriteInfo.size = size; }
	void SetSize(float x, float y) { m_spriteInfo.size = Vector2(x, y); }
	void SetSize(float size) { m_spriteInfo.size = Vector2(size, size); }

	// �摜�̃T�C�Y�ɕύX
	void SetSizeToTexture();

	// UV�I�t�Z�b�g�̐ݒ�
	void SetUVOffset(Vector2 offset) { m_spriteInfo.uvOffset = offset; }

	// UV�X�P�[���̐ݒ�
	void SetUVScale(Vector2 scale) { m_spriteInfo.uvScale = scale; }

	// �������̐ݒ�
	void SetSplit(Vector2 split);

	// �������̐ݒ�
	void SetSplit(int x, int y) { SetSplit(Vector2(x, y)); }

	// �J�����̐ݒ�
	void SetCamera(CameraBase* pCamera) { m_pCamera = pCamera; }

	// �C���f�b�N�X�̐ݒ�
	void SetIndex(int index);

private:
	// �e�N�X�`��
	CameraBase* m_pCamera;
	SpriteInfo m_spriteInfo;
};