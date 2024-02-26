#pragma once
// ====== インクルード部 ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>

// ====== クラス宣言 ======
class TitleUI : public Object
{
public:
	// コンストラクタ
	TitleUI();
	// デストラクタ
	~TitleUI();

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

private:
	// ====== メンバ変数 ======
	SpriteComponent* m_pSprite;

};