#pragma once
// ====== �C���N���[�h�� ======
#include "Enemy.h"

// ====== �N���X�̐錾 ======
class Slime : public Enemy
{
public:
	// �R���X�g���N�^
	Slime() {};
	// �f�X�g���N�^
	~Slime() {};

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Draw() override;

private:
	// �U��
	void Attack() override;

	// �h��
	void Defence() override;

	// �X�L��
	void Skill() override;
};