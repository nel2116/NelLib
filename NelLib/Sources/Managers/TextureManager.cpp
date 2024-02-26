#include "TextureManager.h"
#include <System/Macro.h>

void TextureManager::Init()
{
	// テクスチャの初期化
	for (int i = 0; i < TEX_MAX; ++i)
	{
		m_pTextures[i] = new Texture();
	}

	// テクスチャの読み込み
	{
		WARNINGHR(m_pTextures[TEX_DEFAULT]->Create("Assets/Textures/default.png"), "TEX_DEFAULTが読み込めませんでした。");		// TEX_DEFAULT
		WARNINGHR(m_pTextures[TEX_DEFAULT2]->Create("Assets/Textures/default2.png"), "TEX_DEFAULT2が読み込めませんでした。");	// TEX_DEFAULT2
		WARNINGHR(m_pTextures[TEX_TEST]->Create("Assets/Textures/test.png"), "TEX_TESTが読み込めませんでした。");				// TEX_TEST
		WARNINGHR(m_pTextures[TEX_WALL]->Create("Assets/Textures/wall.png"), "TEX_WALLが読み込めませんでした。");				// TEX_WALL
		WARNINGHR(m_pTextures[TEX_FLOOR]->Create("Assets/Textures/floor.png"), "TEX_FLOORが読み込めませんでした。");			// TEX_FLOOR
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
