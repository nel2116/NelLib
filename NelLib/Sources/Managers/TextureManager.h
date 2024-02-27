#pragma once


// ====== インクルード部 ======
#include <System/Singleton.h>
#include <DirectX/Texture.h>

// ====== クラスの宣言 ======
class TextureManager : public Singleton<TextureManager>
{
public: // enum
	enum TextureType
	{
		TEX_DEFAULT = 0,	// default.png
		TEX_DEFAULT2,		// default2.png
		TEX_TEST,			// test.png
		TEX_WALL,			// wall.png
		TEX_FLOOR,			// floor.png
		TEX_TITLE,			// title.png
		TEX_TITLE_UI,		// titleUI.png
		TEX_BATTLE_UI,		// battleUI.png
		TEX_SLIME,			// slime.png
		TEX_GOBLIN,			// goblin.png
		TEX_BAT,			// bat.png
		// TEX_SPIDER,			// spider.png
		TEX_SKELETON,		// skeleton.png
		TEX_DRAGON,			// dragon.png
		TEX_MAX,
	};

public:
	// デストラクタ
	~TextureManager() { Uninit(); }

	void Init();
	void Uninit();

	// テクスチャの取得
	Texture* GetTexture(const int num);

private:	// メンバ変数
	// テクスチャのリスト
	Texture* m_pTextures[TEX_MAX];

private:	// シングルトン関連
	friend class Singleton<TextureManager>;
	TextureManager() {}
};
// インスタンスを取得するマクロ
#define TEXTURE_MANAGER TextureManager::GetInstance()