#pragma once
// ====== インクルード部 ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>
#include <Components/StatusComponent.h>

// ====== 前方宣言 ======
class Player;

// ====== クラス宣言 ======
// エネミー基底クラス
class Enemy : public Object
{
	enum COMMAND_TYPE
	{
		COMMAND_ATTACK,
		COMMAND_DEFENCE,
		COMMAND_SKILL,
		COMMAND_ESCAPE,

		COMMAND_MAX
	};

public:
	// コンストラクタ
	Enemy();
	// デストラクタ
	~Enemy();

	// 初期化
	virtual void Init() override;

	// 終了
	virtual void Uninit() override;

	// 更新
	virtual void Update() override;

	// 描画
	virtual void Draw() override;

	// ダメージを受けた
	virtual void Damage(int damage);

	// 死亡判定
	// true : 死亡
	// false : 生存
	bool IsDead() { return m_pStatus->GetHp() <= 0; }

	// 行動中かどうか
	// true : 行動中
	// false : 行動中でない
	bool IsAction() { return m_bIsAction; }

	// 行動を開始
	void StartAction() { m_bIsAction = true; }

private:
	// 行動を決定
	void Action();

	// 攻撃
	virtual void Attack();

	// 防御
	virtual void Defence();

	// スキル
	virtual void Skill();

protected:
	// スプライト
	SpriteComponent* m_Sprite;
	// ステータス
	StatusComponent* m_pStatus;
	// コマンド
	COMMAND_TYPE m_Command;
	Player* m_pPlayer;
	bool m_bIsAction;
};
