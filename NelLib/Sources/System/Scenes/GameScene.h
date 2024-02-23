#pragma once
// ====== インクルード ======
#include "Scene.h"

// ====== クラスの宣言 ======
class GameScene : public Scene
{
public:
	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

private:

};