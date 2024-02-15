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