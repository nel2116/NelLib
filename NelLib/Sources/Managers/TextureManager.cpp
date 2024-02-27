#include "TextureManager.h"
#include <System/Macro.h>

void TextureManager::Init()
{
	// �e�N�X�`���̏�����
	for (int i = 0; i < TEX_MAX; ++i)
	{
		m_pTextures[i] = NEW Texture();
	}

	// �e�N�X�`���̓ǂݍ���
	{
		WARNINGHR(m_pTextures[TEX_DEFAULT]->Create("Assets/Textures/default.png"), "TEX_DEFAULT���ǂݍ��߂܂���ł����B");		        // TEX_DEFAULT
		WARNINGHR(m_pTextures[TEX_DEFAULT2]->Create("Assets/Textures/default2.png"), "TEX_DEFAULT2���ǂݍ��߂܂���ł����B");	        // TEX_DEFAULT2
		WARNINGHR(m_pTextures[TEX_TEST]->Create("Assets/Textures/test.png"), "TEX_TEST���ǂݍ��߂܂���ł����B");				        // TEX_TEST
		WARNINGHR(m_pTextures[TEX_WALL]->Create("Assets/Textures/wall.png"), "TEX_WALL���ǂݍ��߂܂���ł����B");				        // TEX_WALL
		WARNINGHR(m_pTextures[TEX_FLOOR]->Create("Assets/Textures/floor.png"), "TEX_FLOOR���ǂݍ��߂܂���ł����B");			        // TEX_FLOOR
		WARNINGHR(m_pTextures[TEX_TITLE]->Create("Assets/Textures/TitleUI/title.png"), "TEX_TITLE���ǂݍ��߂܂���ł����B");			// TEX_TITLE
		WARNINGHR(m_pTextures[TEX_TITLE_UI]->Create("Assets/Textures/TitleUI/tartUI.png"), "TEX_TITLE_UI���ǂݍ��߂܂���ł����B");		// TEX_TITLE_UI
		WARNINGHR(m_pTextures[TEX_BATTLE_UI]->Create("Assets/Textures/battleUI.png"), "TEX_BATTLE_UI���ǂݍ��߂܂���ł����B");			// TEX_BUTTLE_UI
		WARNINGHR(m_pTextures[TEX_SLIME]->Create("Assets/Textures/Enemy/slime.png"), "TEX_SLIME���ǂݍ��߂܂���ł����B");				// TEX_SLIME
		WARNINGHR(m_pTextures[TEX_GOBLIN]->Create("Assets/Textures/Enemy/goblin.png"), "TEX_GOBLIN���ǂݍ��߂܂���ł����B");			// TEX_GOBLIN
		WARNINGHR(m_pTextures[TEX_BAT]->Create("Assets/Textures/Enemy/bat.png"), "TEX_BAT���ǂݍ��߂܂���ł����B");					// TEX_BAT
		// WARNINGHR(m_pTextures[TEX_SPIDER]->Create("Assets/Textures/Enemy/spider.png"), "TEX_SPIDER���ǂݍ��߂܂���ł����B");		// TEX_SPIDER
		WARNINGHR(m_pTextures[TEX_SKELETON]->Create("Assets/Textures/Enemy/skeleton.png"), "TEX_SKELETON���ǂݍ��߂܂���ł����B");	// TEX_SKELETON
		WARNINGHR(m_pTextures[TEX_DRAGON]->Create("Assets/Textures/Enemy/dragon.png"), "TEX_DRAGON���ǂݍ��߂܂���ł����B");			// TEX_DRAGON
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
