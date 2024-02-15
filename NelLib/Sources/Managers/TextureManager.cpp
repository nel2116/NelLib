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
		WARNINGHR(m_pTextures[TEX_DEFAULT]->Create("Assets/Textures/default.png"), "TEX_DEFAULTが読み込めませんでした。");	// TEX_DEFAULT
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
