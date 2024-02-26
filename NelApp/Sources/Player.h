#pragma once
// ====== �C���N���[�h�� ======
#include <Objects/Object.h>
#include <System/Model.h>
#include <DirectX/Shader.h>
#include <Components/StatusComponent.h>

// ====== �O���錾 ======
class Enemy;

// ====== �N���X�錾 ======
class Player : public Object
{
public:
	enum STATE
	{
		STATE_MOVE,
		STATE_BATTLE,
		STATE_MAX
	};

public:
	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;


	// �_���[�W
	void Damage(int damage);

	// ���S����
	// true : ���S
	// false : ����
	bool IsDead() { return m_pStatus->GetHp() <= 0; }

	// ��Ԃ��擾
	STATE GetState() { return m_State; }

	// ��Ԃ�ݒ�
	void SetState(STATE state) { m_State = state; }

	// �퓬�I��
	void EndBattle();

	void SetEnemys(std::vector<Enemy*> pEnemies) { m_pEnemies = pEnemies; }

private:
	// �ړ�
	void Move();

	void Action();

	// �X�e�[�^�X�̕`��
	void DrawStatus();

private:
	float m_fSpeed;
	float m_fRotSpeed;
	Model* m_pModel;
	VertexShader* m_pVS;
	StatusComponent* m_pStatus;
	STATE m_State;
	std::vector<Enemy*> m_pEnemies;
};