#pragma once
// ====== �C���N���[�h�� ======
#include <vector>
#include <System/Singleton.h>
#include <Managers/ObjectsManager.h>
#include "BattleUI.h"

// ====== �O���錾 ======
class Player;
class Enemy;

// ====== �N���X�̐錾 ======
class BattleManager : public Singleton<BattleManager>
{
public:
	// �o�g���̏��
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

	// �o�g���̏�Ԃ��擾
	int GetBattleState() { return m_BattleState; }

	// �o�g�������ǂ���
	bool IsBattle() { return m_BattleState != BATTLE_STATE_END; }

	void EndPlayerTurn();

	void PlayerEscape();

private:	// �����o�ϐ�

	// �o�g���̏��
	BATTLE_STATE m_BattleState;

	// �G�l�~�[�̃��X�g
	std::vector<Enemy*> m_Enemys;

	Player* m_pPlayer;
	BattleUI* m_BattleUI;

private:
	// �V���O���g���֘A
	friend class Singleton<BattleManager>;
	BattleManager() : m_BattleState(BATTLE_STATE_END), m_pPlayer(nullptr), m_BattleUI(nullptr) {}
};
// �C���X�^���X�̎擾
#define BATTLE_MANAGER BattleManager::GetInstance()