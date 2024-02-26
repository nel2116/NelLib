#pragma once
// ====== インクルード部 ======
#include "Enemy.h"

// ====== クラスの宣言 ======
class Slime : public Enemy
{
public:
	// コンストラクタ
	Slime() {};
	// デストラクタ
	~Slime() {};

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Draw() override;

private:
	// 攻撃
	void Attack() override;

	// 防御
	void Defence() override;

	// スキル
	void Skill() override;
};