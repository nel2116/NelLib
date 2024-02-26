#pragma once
// ====== インクルード ======
#include <System/Scenes/Scene.h>
#include <TitleUI.h>

// ====== クラスの宣言 ======
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene() {}

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

private:
	// シーンの名前
	TitleUI* m_TitleUI;
};