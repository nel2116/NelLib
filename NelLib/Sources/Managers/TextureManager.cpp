#include "TextureManager.h"
#include <System/Macro.h>

void TextureManager::Init()
{
	// �e�N�X�`���̏�����
	for (int i = 0; i < TEX_MAX; ++i)
	{
		m_pTextures[i] = new Texture();
	}

	// �e�N�X�`���̓ǂݍ���
	{
		WARNINGHR(m_pTextures[TEX_DEFAULT]->Create("Assets/Textures/default.png"), "TEX_DEFAULT���ǂݍ��߂܂���ł����B");	// TEX_DEFAULT
	}
}

void TextureManager::Uninit()
{
	// �e�N�X�`���̉��
	for (int i = 0; i < TEX_MAX; ++i)
	{
		SAFE_DELETE(m_pTextures[i]);
	}
}

Texture* TextureManager::GetTexture(const int num)
{
	return m_pTextures[num];
}
