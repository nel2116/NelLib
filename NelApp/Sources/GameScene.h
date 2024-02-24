#pragma once
// ====== インクルード ======
#include <System/Scenes/Scene.h>
#include "Field.h"
#include "Player.h"

// ====== クラスの宣言 ======
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene() {}

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

private:
	Field* m_Field;
	Player* m_Player;
};