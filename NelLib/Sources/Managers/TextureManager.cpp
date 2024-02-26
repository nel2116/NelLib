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
		WARNINGHR(m_pTextures[TEX_DEFAULT]->Create("Assets/Textures/default.png"), "TEX_DEFAULT���ǂݍ��߂܂���ł����B");		// TEX_DEFAULT
		WARNINGHR(m_pTextures[TEX_DEFAULT2]->Create("Assets/Textures/default2.png"), "TEX_DEFAULT2���ǂݍ��߂܂���ł����B");	// TEX_DEFAULT2
		WARNINGHR(m_pTextures[TEX_TEST]->Create("Assets/Textures/test.png"), "TEX_TEST���ǂݍ��߂܂���ł����B");				// TEX_TEST
		WARNINGHR(m_pTextures[TEX_WALL]->Create("Assets/Textures/wall.png"), "TEX_WALL���ǂݍ��߂܂���ł����B");				// TEX_WALL
		WARNINGHR(m_pTextures[TEX_FLOOR]->Create("Assets/Textures/floor.png"), "TEX_FLOOR���ǂݍ��߂܂���ł����B");			// TEX_FLOOR
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
