#pragma once
// ====== �C���N���[�h�� ======
#include <string>
#include <Components/Component.h>

// ====== �O���錾 ======

// ====== �N���X�̐錾 ======
class StatusComponent : public Component
{
public:
	struct Status
	{
		std::string name;
		int level;
		int hp;
		int maxHp;
		int mp;
		int maxMp;
		float attack;
		float defence;
		float speed;
		float xp;
		float maxXp;
		int gold;
		float physicalResistance;
		float magicResistance;

		// �R���X�g���N�^
		Status()
		{
			name = "";
			level = 1;
			hp = 0;
			maxHp = 0;
			mp = 0;
			maxMp = 0;
			attack = 0.0f;
			defence = 0.0f;
			speed = 0.0f;
			xp = 0.0f;
			maxXp = 0.0f;
			gold = 0;
			physicalResistance = 0.0f;
			magicResistance = 0.0f;
		}
	};

public:
	// �R���X�g���N�^
	StatusComponent(Object* pObject);

	// �f�X�g���N�^
	~StatusComponent() {}

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

	// ���x���̐ݒ�
	void SetLevel(int level) { m_Status.level = level; }

	// ���x���̎擾
	int GetLevel() { return m_Status.level; }

	// HP�̐ݒ�
	void SetHp(int hp) { m_Status.hp = hp; }

	// HP�̎擾
	int GetHp() { return m_Status.hp; }

	// �ő�HP�̐ݒ�
	void SetMaxHp(int maxHp) { m_Status.maxHp = maxHp; }

	// �ő�HP�̎擾
	int GetMaxHp() { return m_Status.maxHp; }

	// MP�̐ݒ�
	void SetMp(int mp) { m_Status.mp = mp; }

	// MP�̎擾
	int GetMp() { return m_Status.mp; }

	// �ő�MP�̐ݒ�
	void SetMaxMp(int maxMp) { m_Status.maxMp = maxMp; }

	// �ő�MP�̎擾
	int GetMaxMp() { return m_Status.maxMp; }

	// �U���͂̐ݒ�
	void SetAttack(float attack) { m_Status.attack = attack; }

	// �U���͂̎擾
	float GetAttack() { return m_Status.attack; }

	// �h��͂̐ݒ�
	void SetDefence(float defence) { m_Status.defence = defence; }

	// �h��͂̎擾
	float GetDefence() { return m_Status.defence; }

	// �X�s�[�h�̐ݒ�
	void SetSpeed(float speed) { m_Status.speed = speed; }

	// �X�s�[�h�̎擾
	float GetSpeed() { return m_Status.speed; }

	// �o���l�̐ݒ�
	void SetXp(float xp) { m_Status.xp = xp; }

	// �o���l�̎擾
	float GetXp() { return m_Status.xp; }

	// �ő�o���l�̐ݒ�
	void SetMaxXp(float maxXp) { m_Status.maxXp = maxXp; }

	// �ő�o���l�̎擾
	float GetMaxXp() { return m_Status.maxXp; }

	// �S�[���h�̐ݒ�
	void SetGold(int gold) { m_Status.gold = gold; }

	// �S�[���h�̎擾
	int GetGold() { return m_Status.gold; }

	// �����ϐ��̐ݒ�
	void SetPhysicalResistance(float physicalResistance) { m_Status.physicalResistance = physicalResistance; }

	// �����ϐ��̎擾
	float GetPhysicalResistance() { return m_Status.physicalResistance; }

	// ���@�ϐ��̐ݒ�
	void SetMagicResistance(float magicResistance) { m_Status.magicResistance = magicResistance; }

	// ���@�ϐ��̎擾
	float GetMagicResistance() { return m_Status.magicResistance; }

	// ���O�̐ݒ�
	void SetName(std::string name) { m_Status.name = name; }

	// ���O�̎擾
	std::string GetName() { return m_Status.name; }

private:
	// �X�e�[�^�X
	Status m_Status;
};