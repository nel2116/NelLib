#pragma once
// ====== �C���N���[�h�� ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>
#include <Components/StatusComponent.h>

// ====== �O���錾 ======
class Player;

// ====== �N���X�錾 ======
// �G�l�~�[���N���X
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
	// �R���X�g���N�^
	Enemy();
	// �f�X�g���N�^
	~Enemy();

	// ������
	virtual void Init() override;

	// �I��
	virtual void Uninit() override;

	// �X�V
	virtual void Update() override;

	// �`��
	virtual void Draw() override;

	// �_���[�W���󂯂�
	virtual void Damage(int damage);

	// ���S����
	// true : ���S
	// false : ����
	bool IsDead() { return m_pStatus->GetHp() <= 0; }

	// �s�������ǂ���
	// true : �s����
	// false : �s�����łȂ�
	bool IsAction() { return m_bIsAction; }

	// �s�����J�n
	void StartAction() { m_bIsAction = true; }

private:
	// �s��������
	void Action();

	// �U��
	virtual void Attack();

	// �h��
	virtual void Defence();

	// �X�L��
	virtual void Skill();

protected:
	// �X�v���C�g
	SpriteComponent* m_Sprite;
	// �X�e�[�^�X
	StatusComponent* m_pStatus;
	// �R�}���h
	COMMAND_TYPE m_Command;
	Player* m_pPlayer;
	bool m_bIsAction;
};
