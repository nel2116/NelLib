#pragma once

// ====== インクルード部 ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>

// ====== クラスの宣言 ======
class UI_TestObject : public Object
{
public:
	// コンストラクタ
	UI_TestObject() {}
	// デストラクタ
	~UI_TestObject() {}

	// 初期化
	void Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:
	// スプライトコンポーネント
	SpriteComponent* m_pSprite;
};