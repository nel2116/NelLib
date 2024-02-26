#pragma once

// ====== インクルード部 ======
#include <DirectX/Texture.h>
#include <Components/Component.h>
#include <Objects/Camera/CameraUI.h>

// ====== 前方宣言 ======
#define NORMAL_TEX_VEC Vector3(6.4f, 3.6f, 1.0f)

// ====== クラスの宣言 ======
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

		// コンストラクタ
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
	// コンストラクタ
	SpriteComponent(Object* pObject);

	// デストラクタ
	~SpriteComponent() {}

	// 初期化
	void Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

	// テクスチャの設定
	void SetTexture(Texture* tex) { m_spriteInfo.texture = tex; }

	// カラーの設定
	void SetColor(Vector4 color) { m_spriteInfo.color = color; }

	void SetAlpha(float alpha) { m_spriteInfo.color.w = alpha; }

	// サイズの設定
	void SetSize(Vector2 size) { m_spriteInfo.size = size; }
	void SetSize(float x, float y) { m_spriteInfo.size = Vector2(x, y); }
	void SetSize(float size) { m_spriteInfo.size = Vector2(size, size); }

	// 画像のサイズに変更
	void SetSizeToTexture();

	// UVオフセットの設定
	void SetUVOffset(Vector2 offset) { m_spriteInfo.uvOffset = offset; }

	// UVスケールの設定
	void SetUVScale(Vector2 scale) { m_spriteInfo.uvScale = scale; }

	// 分割数の設定
	void SetSplit(Vector2 split);

	// 分割数の設定
	void SetSplit(int x, int y) { SetSplit(Vector2(x, y)); }

	// カメラの設定
	void SetCamera(CameraBase* pCamera) { m_pCamera = pCamera; }

	// インデックスの設定
	void SetIndex(int index);

private:
	// テクスチャ
	CameraBase* m_pCamera;
	SpriteInfo m_spriteInfo;
};