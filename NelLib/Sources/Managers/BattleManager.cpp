#include "BattleManager.h"
#include <Managers/SceneManager.h>
#include <EnemyFactory.h>
#include <Player.h>
#include <Enemy.h>

void BattleManager::Init()
{
}

void BattleManager::Uninit()
{
}

void BattleManager::Update()
{
	// バトルが終了している場合は、更新処理を行わない
	if (m_BattleState == BATTLE_STATE_END) { return; }

	m_pPlayer = OBJECTS_MANAGER.GetObjects<Player>();
	if (!m_pPlayer) { return; }

	if (m_BattleState == BATTLE_STATE_ENEMY_TURN)
	{
		// 全エネミーの行動フラグを立てる
		for (int i = 0; i < m_Enemys.size(); ++i)
		{
			m_Enemys[i]->StartAction();
		}
	}

	// エネミーが全滅しているかどうかの判定
	// すべてのエネミーの行動が終わっているかどうか判定
	bool IsAllEnemyDead = false;
	int IsAllEnemyDeadCount = 0;
	int IsAllEnemyActionCount = 0;

	for (int i = 0; i < m_Enemys.size(); ++i)
	{
		if (m_Enemys[i]->IsDead()) { IsAllEnemyDeadCount++; }
		if (!m_Enemys[i]->IsAction()) { IsAllEnemyActionCount++; }
	}

	if (IsAllEnemyDeadCount == m_Enemys.size()) { IsAllEnemyDead = true; }
	if (IsAllEnemyActionCount == m_Enemys.size()) { m_BattleState = BATTLE_STATE_PLAYER_TURN; }

	if (IsAllEnemyDead)
	{
		// バトルの状態を終了に設定
		m_BattleState = BATTLE_STATE_END;

		// リストのお片付け
		for (int i = 0; i < m_Enemys.size(); ++i)
		{
			m_Enemys[i]->Destroy();
		}
		m_Enemys.clear();

		// バトル終了時のメッセージを表示

		// プレイヤーの状態を移動に設定
		m_pPlayer->EndBattle();
	}
	// プレイヤーが死んでいるのならシーンを変える
	if (m_pPlayer->IsDead()) { SCENE_MANAGER.ChangeScene("TitleScene"); }
}

void BattleManager::Draw()
{
}

void BattleManager::BattleStart()
{
	m_pPlayer = OBJECTS_MANAGER.GetObjects<Player>();

	// プレイヤーの状態をバトルに設定
	m_pPlayer->SetState(Player::STATE_BATTLE);

	// 戦闘を行うエネミーの数をランダムに決定
	// 最小 : 1, 最大 : 3
	int enemyNum = rand() % 3;

	// リストのサイズを変更する
	m_Enemys.resize(enemyNum);

	// 戦闘を行うエネミーを生成
	for (int i = 0; i < enemyNum; i++)
	{
		m_Enemys[i] = EnemyFactory::CreateEnemy(0);
	}

	// エネミーのポインタをプレイヤーに設定
	m_pPlayer->SetEnemys(m_Enemys);

	// バトルの状態をプレイヤーのターンに設定
	m_BattleState = BATTLE_STATE_PLAYER_TURN;

	// バトル開始時のメッセージを表示
	// TODO : メッセージ表示処理

	// バトル開始時のBGMを再生
	// TODO : BGM再生処理

	// バトル開始時のSEを再生
	// TODO : SE再生処理

	// バトル開始時の演出を再生
	// TODO : 演出再生処理
}

void BattleManager::EndPlayerTurn()
{
	// バトルの状態をエネミーのターンに設定
	m_BattleState = BATTLE_STATE_ENEMY_TURN;
}
