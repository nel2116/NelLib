#pragma once

// ====== �C���N���[�h�� ======

class Object;

// �e�U�镑������������R���|�[�l���g�̊��N���X
class Component
{
public:
	// �R���X�g���N�^
	Component(Object* owner) : owner(owner), order(50), enable(true), destroy(false) {}

	// �f�X�g���N�^
	virtual ~Component() {}

	// ����������
	virtual void Init() = 0;

	// �X�V����
	virtual void Update() {}

	// �`�揈��
	virtual void Draw() {}

	// �I������
	virtual void Uninit() = 0;

	// �I�[�_�[�̎擾
	int GetOrder() { return order; }
	// �I�[�_�[�̐ݒ�
	void SetOrder(int order) { this->order = order; }

	// �L�����ǂ����̎擾
	bool IsEnable() { return enable; }
	// �L�����ǂ����̐ݒ�
	void SetEnable(bool enable) { this->enable = enable; }

	// �I�[�i�[�I�u�W�F�N�g�̎擾
	Object* GetOwner() { return owner; }

	// �j�����邩�ǂ����̎擾
	bool IsDestroy() { return destroy; }
	// �j�����邩�ǂ����̐ݒ�
	void Destroy() { destroy = true; enable = false; }


private:
	Object* owner;	// �I�[�i�[�I�u�W�F�N�g
	int order;		// �e�R���|�[�l���g�̏������鏇��,�l���������قǑ������������
	bool enable;	// �L�����ǂ���
	bool destroy;	// �j�����邩�ǂ���
};