#pragma once


// ====== �C���N���[�h�� ======
#include <System/Singleton.h>
#include <DirectX/Texture.h>

// ====== �N���X�̐錾 ======
class TextureManager : public Singleton<TextureManager>
{
public: // enum
	enum TextureType
	{
		TEX_DEFAULT = 0,	// default.png
		TEX_MAX,
	};

public:
	// �f�X�g���N�^
	~TextureManager() { Uninit(); }

	void Init();
	void Uninit();

	// �e�N�X�`���̎擾
	Texture* GetTexture(const int num);

private:	// �����o�ϐ�
	// �e�N�X�`���̃��X�g
	Texture* m_pTextures[TEX_MAX];

private:	// �V���O���g���֘A
	friend class Singleton<TextureManager>;
	TextureManager() {}
};
// �C���X�^���X���擾����}�N��
#define TEXTURE_MANAGER TextureManager::GetInstance()