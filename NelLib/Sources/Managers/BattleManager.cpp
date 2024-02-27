#include "BattleManager.h"
#include <Managers/SceneManager.h>
#include <Managers/TextManager.h>
#include <EnemyFactory.h>
#include <Player.h>
#include <Enemy.h>

void BattleManager::Init()
{
	m_BattleUI = OBJECTS_MANAGER.AddObject<BattleUI>();
	m_BattleUI->Init();
	m_BattleUI->SetEnable(false);
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
		TEXT_MANAGER.AddText("モンスターを倒した！", Vector2(490.0f, 200.0f), 120);

		// バトルUIを非表示
		m_BattleUI->SetEnable(false);

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
//	int enemyNum = rand() % 3 + 1;
	int enemyNum = 3;

	// リストのサイズを変更する
	m_Enemys.resize(enemyNum);

	// 戦闘を行うエネミーを生成
	for (int i = 0; i < enemyNum; i++)
	{
		m_Enemys[i] = EnemyFactory::CreateEnemy(0);
		Vector3 pos = Vector3(-0.3f + (float)i * 1.1f, 0.0f, 0.0f);
		// 二体目のエネミーのみ、位置を調整
		if (i == 1) { pos.y += 0.2f; }
		m_Enemys[i]->GetTransform()->SetPosition(pos);
	}

	// エネミーのポインタをプレイヤーに設定
	m_pPlayer->SetEnemys(m_Enemys);

	// バトルの状態をプレイヤーのターンに設定
	m_BattleState = BATTLE_STATE_PLAYER_TURN;

	// バトルUIを表示
	m_BattleUI->SetEnable(true);

	// バトル開始時のメッセージを表示
	TEXT_MANAGER.AddText("モンスターが現れた！", Vector2(500.0f, 490.0f), 110);
	for (int i = 0; i < m_Enemys.size(); ++i)
	{
		TEXT_MANAGER.AddText(m_Enemys[i]->GetName() + "が現れた！", Vector2(500.0f, 530.0f + (30.0f * i)), 120);
	};

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
