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
	// �o�g�����I�����Ă���ꍇ�́A�X�V�������s��Ȃ�
	if (m_BattleState == BATTLE_STATE_END) { return; }

	m_pPlayer = OBJECTS_MANAGER.GetObjects<Player>();
	if (!m_pPlayer) { return; }

	if (m_BattleState == BATTLE_STATE_ENEMY_TURN)
	{
		// �S�G�l�~�[�̍s���t���O�𗧂Ă�
		for (int i = 0; i < m_Enemys.size(); ++i)
		{
			m_Enemys[i]->StartAction();
		}
	}

	// �G�l�~�[���S�ł��Ă��邩�ǂ����̔���
	// ���ׂẴG�l�~�[�̍s�����I����Ă��邩�ǂ�������
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
		// �o�g���̏�Ԃ��I���ɐݒ�
		m_BattleState = BATTLE_STATE_END;

		// ���X�g�̂��Еt��
		for (int i = 0; i < m_Enemys.size(); ++i)
		{
			m_Enemys[i]->Destroy();
		}
		m_Enemys.clear();

		// �o�g���I�����̃��b�Z�[�W��\��

		// �v���C���[�̏�Ԃ��ړ��ɐݒ�
		m_pPlayer->EndBattle();
	}
	// �v���C���[������ł���̂Ȃ�V�[����ς���
	if (m_pPlayer->IsDead()) { SCENE_MANAGER.ChangeScene("TitleScene"); }
}

void BattleManager::Draw()
{
}

void BattleManager::BattleStart()
{
	m_pPlayer = OBJECTS_MANAGER.GetObjects<Player>();

	// �v���C���[�̏�Ԃ��o�g���ɐݒ�
	m_pPlayer->SetState(Player::STATE_BATTLE);

	// �퓬���s���G�l�~�[�̐��������_���Ɍ���
	// �ŏ� : 1, �ő� : 3
	int enemyNum = rand() % 3;

	// ���X�g�̃T�C�Y��ύX����
	m_Enemys.resize(enemyNum);

	// �퓬���s���G�l�~�[�𐶐�
	for (int i = 0; i < enemyNum; i++)
	{
		m_Enemys[i] = EnemyFactory::CreateEnemy(0);
	}

	// �G�l�~�[�̃|�C���^���v���C���[�ɐݒ�
	m_pPlayer->SetEnemys(m_Enemys);

	// �o�g���̏�Ԃ��v���C���[�̃^�[���ɐݒ�
	m_BattleState = BATTLE_STATE_PLAYER_TURN;

	// �o�g���J�n���̃��b�Z�[�W��\��
	// TODO : ���b�Z�[�W�\������

	// �o�g���J�n����BGM���Đ�
	// TODO : BGM�Đ�����

	// �o�g���J�n����SE���Đ�
	// TODO : SE�Đ�����

	// �o�g���J�n���̉��o���Đ�
	// TODO : ���o�Đ�����
}

void BattleManager::EndPlayerTurn()
{
	// �o�g���̏�Ԃ��G�l�~�[�̃^�[���ɐݒ�
	m_BattleState = BATTLE_STATE_ENEMY_TURN;
}
