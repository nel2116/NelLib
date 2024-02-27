#include "TextureManager.h"
#include <System/Macro.h>

void TextureManager::Init()
{
	// テクスチャの初期化
	for (int i = 0; i < TEX_MAX; ++i)
	{
		m_pTextures[i] = NEW Texture();
	}

	// テクスチャの読み込み
	{
		WARNINGHR(m_pTextures[TEX_DEFAULT]->Create("Assets/Textures/default.png"), "TEX_DEFAULTが読み込めませんでした。");		        // TEX_DEFAULT
		WARNINGHR(m_pTextures[TEX_DEFAULT2]->Create("Assets/Textures/default2.png"), "TEX_DEFAULT2が読み込めませんでした。");	        // TEX_DEFAULT2
		WARNINGHR(m_pTextures[TEX_TEST]->Create("Assets/Textures/test.png"), "TEX_TESTが読み込めませんでした。");				        // TEX_TEST
		WARNINGHR(m_pTextures[TEX_WALL]->Create("Assets/Textures/wall.png"), "TEX_WALLが読み込めませんでした。");				        // TEX_WALL
		WARNINGHR(m_pTextures[TEX_FLOOR]->Create("Assets/Textures/floor.png"), "TEX_FLOORが読み込めませんでした。");			        // TEX_FLOOR
		WARNINGHR(m_pTextures[TEX_TITLE]->Create("Assets/Textures/TitleUI/title.png"), "TEX_TITLEが読み込めませんでした。");			// TEX_TITLE
		WARNINGHR(m_pTextures[TEX_TITLE_UI]->Create("Assets/Textures/TitleUI/tartUI.png"), "TEX_TITLE_UIが読み込めませんでした。");		// TEX_TITLE_UI
		WARNINGHR(m_pTextures[TEX_BATTLE_UI]->Create("Assets/Textures/battleUI.png"), "TEX_BATTLE_UIが読み込めませんでした。");			// TEX_BUTTLE_UI
		WARNINGHR(m_pTextures[TEX_SLIME]->Create("Assets/Textures/Enemy/slime.png"), "TEX_SLIMEが読み込めませんでした。");				// TEX_SLIME
		WARNINGHR(m_pTextures[TEX_GOBLIN]->Create("Assets/Textures/Enemy/goblin.png"), "TEX_GOBLINが読み込めませんでした。");			// TEX_GOBLIN
		WARNINGHR(m_pTextures[TEX_BAT]->Create("Assets/Textures/Enemy/bat.png"), "TEX_BATが読み込めませんでした。");					// TEX_BAT
		// WARNINGHR(m_pTextures[TEX_SPIDER]->Create("Assets/Textures/Enemy/spider.png"), "TEX_SPIDERが読み込めませんでした。");		// TEX_SPIDER
		WARNINGHR(m_pTextures[TEX_SKELETON]->Create("Assets/Textures/Enemy/skeleton.png"), "TEX_SKELETONが読み込めませんでした。");	// TEX_SKELETON
		WARNINGHR(m_pTextures[TEX_DRAGON]->Create("Assets/Textures/Enemy/dragon.png"), "TEX_DRAGONが読み込めませんでした。");			// TEX_DRAGON
	}
}

void TextureManager::Uninit()
{
	// テクスチャの解放
	for (int i = 0; i < TEX_MAX; ++i)
	{
		SAFE_DELETE(m_pTextures[i]);
	}
}

Texture* TextureManager::GetTexture(const int num)
{
	return m_pTextures[num];
}
