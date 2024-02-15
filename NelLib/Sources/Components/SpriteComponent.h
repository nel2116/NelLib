#pragma once

// ====== インクルード部 ======
#include <DirectX/Texture.h>
#include <Components/Component.h>

// ====== クラスの宣言 ======
class SpriteComponent : public Component
{

public:
	// コンストラクタ
	SpriteComponent(class Object* owner) : Component(owner), m_pTex(nullptr) {}
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
	void SetTexture(Texture* tex) { m_pTex = tex; }

private:
	// テクスチャ
	Texture* m_pTex;
};