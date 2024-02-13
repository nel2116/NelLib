#pragma once

// ====== �C���N���[�h�� ======
#include <vector>
#include <algorithm>
#include <Components/Component.h>
#include <System/Macro.h>
#include <Objects/Camera/CameraBase.h>

// �Q�[���I�u�W�F�N�g�̊��N���X
class Object
{
public:
	// �R���X�g���N�^
	Object() : order(50), enable(true), destroy(false), parent(nullptr), camera{}

		// �f�X�g���N�^
	virtual ~Object();

	// ����������
	virtual void Init() {}

	// �X�V����
	virtual void Update() {}

	// �`�揈��
	virtual void Draw() {}

	// �I������
	virtual void Uninit() = 0;

public:	// �Q�b�^�[�Z�b�^�[

	// �I�[�_�[�̎擾
	int GetOrder() { return order; }
	// �I�[�_�[�̐ݒ�
	void SetOrder(int order) { this->order = order; }
	// �L�����ǂ����̎擾
	bool IsEnable() { return enable; }
	// �L�����ǂ����̐ݒ�
	void SetEnable(bool enable) { this->enable = enable; }
	// �j�����邩�ǂ����̎擾
	bool IsDestroy() { return destroy; }
	// �j�����邩�ǂ����̐ݒ�
	void Destroy() { destroy = true; enable = false; }
	// �J�����̐ݒ�
	void SetCamera(CameraBase* camera) { this->camera = camera; }

public:	// �e�q�֌W
	// �e�I�u�W�F�N�g�̎擾
	Object* GetParent() { return parent; }
	// �e�I�u�W�F�N�g�̐ݒ�
	void SetParent(Object* parent) { this->parent = parent; }
	// �e�q�֌W�̔j��
	void RemoveParent() { parent = nullptr; }

public:	// �R���|�[�l���g�֘A

	// �R���|�[�l���g�̒ǉ�
	template <typename T>
	T* AddComponent()
	{
		// ���łɓ����R���|�[�l���g���A�^�b�`����Ă���ꍇ�͒ǉ����Ȃ�
		for (auto component : components)
		{
			T* castComponent = dynamic_cast<T*>(component);
			if (castComponent != nullptr)
			{
				return castComponent;
			}
		}
		// �V���ɒǉ����ꂽ�R���|�[�l���g���ꎞ�I�ɕێ�����
		T* newComponent = NEW T(this);
		newComponents.push_back(newComponent);
		return newComponent;
	}

	// �R���|�[�l���g�̎擾
	template <typename T>
	T* GetComponent()
	{
		for (auto component : components)
		{
			T* castComponent = dynamic_cast<T*>(component);
			if (castComponent != nullptr)
			{
				return castComponent;
			}
		}
		return nullptr;
	}

	// �R���|�[�l���g�̍X�V
	void UpdateComponents();

	// �R���|�[�l���g�̕`��
	void DrawComponents();

private:
	// �R���|�[�l���g���I�[�_�[�̏��Ԃɕ��ёւ���
	void SortComponents();

private:	// �����o�ϐ�
	// �R���|�[�l���g�̃��X�g
	std::vector<Component*> components;
	// �R���|�[�l���g�̍X�V���ɔz�񂪕ύX�����ƃC�e���[�^�������ɂȂ�̂ŁA�V���ɒǉ����ꂽ�R���|�[�l���g���ꎞ�I�ɕێ�����
	std::vector<Component*> newComponents;
	int order;		// �e�I�u�W�F�N�g�̏������鏇��,�l���������قǑ������������
	bool enable;	// �L�����ǂ���
	bool destroy;	// �j�����邩�ǂ���
	CameraBase* camera;	// �J����
	Object* parent;	// �e�I�u�W�F�N�g
};