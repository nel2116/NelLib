#include "Enemy.h"
#include <Player.h>
#include <Managers/ObjectsManager.h>
#include <Managers/BattleManager.h>

Enemy::Enemy()
	: m_pStatus(nullptr)
	, m_Sprite(nullptr)
	, m_pPlayer(nullptr)
	, m_Command(COMMAND_ATTACK)
	, m_bIsAction(false)
{
	m_pStatus = AddComponent<StatusComponent>();
	m_Sprite = AddComponent<SpriteComponent>();
}

Enemy::~Enemy()
{
	m_Sprite = nullptr;
	m_pStatus = nullptr;
}

void Enemy::Init()
{
	m_pPlayer = OBJECTS_MANAGER.GetObjects<Player>();
	// ステータスを初期化
	m_pStatus->SetLevel(1);
	m_pStatus->SetHp(100);
	m_pStatus->SetMaxHp(100);
	m_pStatus->SetMp(0);
	m_pStatus->SetMaxMp(0);
	m_pStatus->SetAttack(10);
	m_pStatus->SetDefence(5);
	m_pStatus->SetSpeed(5);
	m_pStatus->SetXp(0);
	m_pStatus->SetMaxXp(100);
	m_pStatus->SetGold(0);
	m_pStatus->SetMagicResistance(0);
	m_pStatus->SetPhysicalResistance(0);
}

void Enemy::Uninit()
{
	m_pPlayer = nullptr;
}

void Enemy::Update()
{
	if (BATTLE_MANAGER.GetBattleState() == BattleManager::BATTLE_STATE_ENEMY_TURN) { Action(); }
}

void Enemy::Draw()
{
}

void Enemy::Damage(int damage)
{
	// ダメージを受ける
	m_pStatus->SetHp(m_pStatus->GetHp() - damage);
}

void Enemy::Action()
{
	// 死んでいる場合は行動しない
	if (IsDead()) { return; }

	// 行動中フラグが立っていない場合は行動しない
	if (!m_bIsAction) { return; }

	// 逃亡以外の行動をランダムに決定
	m_Command = (COMMAND_TYPE)(rand() % COMMAND_MAX - 1);

	// 逃亡判定
	if (m_pStatus->GetHp() < m_pStatus->GetMaxHp() / 2)
	{
		m_Command = (COMMAND_TYPE)(rand() % COMMAND_MAX);
	}

	if (m_Command != COMMAND_ESCAPE)
	{
		// 逃亡以外の行動
		switch (m_Command)
		{
		case COMMAND_ATTACK:
			// 攻撃処理
			Attack();
			break;
		case COMMAND_DEFENCE:
			// 防御処理
			Defence();
			break;
		case COMMAND_SKILL:
			// スキル処理
			Skill();
			break;
		}
	}

	// 行動が終わったら、行動中フラグを下ろす
	m_bIsAction = false;
}

void Enemy::Attack()
{
	// プレイヤーにダメージを与える
	m_pPlayer->Damage(10);

	// 攻撃時の演出を再生
	// TODO : 演出再生処理

	// 攻撃時のSEを再生
	// TODO : SE再生処理

	// 攻撃時のメッセージを表示
	// TODO : メッセージ表示処理
}

void Enemy::Defence()
{
	m_pStatus->SetDefence(m_pStatus->GetDefence() * 1.3f);
	// 防御時の演出を再生
	// TODO : 演出再生処理

	// 防御時のSEを再生
	// TODO : SE再生処理

	// 防御時のメッセージを表示
	// TODO : メッセージ表示処理
}

void Enemy::Skill()
{
}
