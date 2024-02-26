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
	// �X�e�[�^�X��������
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
	// �_���[�W���󂯂�
	m_pStatus->SetHp(m_pStatus->GetHp() - damage);
}

void Enemy::Action()
{
	// ����ł���ꍇ�͍s�����Ȃ�
	if (IsDead()) { return; }

	// �s�����t���O�������Ă��Ȃ��ꍇ�͍s�����Ȃ�
	if (!m_bIsAction) { return; }

	// ���S�ȊO�̍s���������_���Ɍ���
	m_Command = (COMMAND_TYPE)(rand() % COMMAND_MAX - 1);

	// ���S����
	if (m_pStatus->GetHp() < m_pStatus->GetMaxHp() / 2)
	{
		m_Command = (COMMAND_TYPE)(rand() % COMMAND_MAX);
	}

	if (m_Command != COMMAND_ESCAPE)
	{
		// ���S�ȊO�̍s��
		switch (m_Command)
		{
		case COMMAND_ATTACK:
			// �U������
			Attack();
			break;
		case COMMAND_DEFENCE:
			// �h�䏈��
			Defence();
			break;
		case COMMAND_SKILL:
			// �X�L������
			Skill();
			break;
		}
	}

	// �s�����I�������A�s�����t���O�����낷
	m_bIsAction = false;
}

void Enemy::Attack()
{
	// �v���C���[�Ƀ_���[�W��^����
	m_pPlayer->Damage(10);

	// �U�����̉��o���Đ�
	// TODO : ���o�Đ�����

	// �U������SE���Đ�
	// TODO : SE�Đ�����

	// �U�����̃��b�Z�[�W��\��
	// TODO : ���b�Z�[�W�\������
}

void Enemy::Defence()
{
	m_pStatus->SetDefence(m_pStatus->GetDefence() * 1.3f);
	// �h�䎞�̉��o���Đ�
	// TODO : ���o�Đ�����

	// �h�䎞��SE���Đ�
	// TODO : SE�Đ�����

	// �h�䎞�̃��b�Z�[�W��\��
	// TODO : ���b�Z�[�W�\������
}

void Enemy::Skill()
{
}
