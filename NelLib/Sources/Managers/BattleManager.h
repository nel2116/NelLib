#pragma once
// ====== インクルード部 ======
#include <vector>
#include <System/Singleton.h>
#include <Managers/ObjectsManager.h>
#include "BattleUI.h"

// ====== 前方宣言 ======
class Player;
class Enemy;

// ====== クラスの宣言 ======
class BattleManager : public Singleton<BattleManager>
{
public:
	// バトルの状態
	enum BATTLE_STATE
	{
		BATTLE_STATE_START,
		BATTLE_STATE_PLAYER_TURN,
		BATTLE_STATE_ENEMY_TURN,
		BATTLE_STATE_END,
		BATTLE_STATE_MAX,
	};

public:
	~BattleManager() {}

	void Init();

	void Uninit();

	void Update();

	void Draw();

	void BattleStart();

	// バトルの状態を取得
	int GetBattleState() { return m_BattleState; }

	// バトル中かどうか
	bool IsBattle() { return m_BattleState != BATTLE_STATE_END; }

	void EndPlayerTurn();

	void PlayerEscape();

private:	// メンバ変数

	// バトルの状態
	BATTLE_STATE m_BattleState;

	// エネミーのリスト
	std::vector<Enemy*> m_Enemys;

	Player* m_pPlayer;
	BattleUI* m_BattleUI;

private:
	// シングルトン関連
	friend class Singleton<BattleManager>;
	BattleManager() : m_BattleState(BATTLE_STATE_END), m_pPlayer(nullptr), m_BattleUI(nullptr) {}
};
// インスタンスの取得
#define BATTLE_MANAGER BattleManager::GetInstance()