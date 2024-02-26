#pragma once
// ====== インクルード部 ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>

// ====== クラス宣言 ======
class Fade : public Object
{
public:
	// フェードの状態
	enum FADE_STATE
	{
		FADE_NONE,
		FADE_IN,
		FADE_OUT
	};

public:
	// コンストラクタ
	Fade();
	// デストラクタ
	~Fade();

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	// フェードイン
	void FadeIn(float time);

	// フェードアウト
	void FadeOut(float time);

	// フェード中かどうか
	// true : フェード中
	// false : フェード中でない
	bool IsFade() { return m_FadeState != FADE_NONE; }

	// フェードの状態を取得
	FADE_STATE GetState() { return m_FadeState; }

private:
	// フェードの状態
	FADE_STATE m_FadeState;

	// フェードの時間
	float m_fFadeTime;

	// フェードの時間カウント
	float m_fFadeTimeCount;

	// アルファ値
	float m_fAlpha;

	// フェードのテクスチャ
	SpriteComponent* m_pSprite;
};