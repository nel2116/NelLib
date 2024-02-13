#pragma once

// ====== �C���N���[�h�� ======
#include <vector>
#include <Objects/Object.h>
#include <System/Macro.h>
#include "CameraManager.h"

class ObjectsManager
{
public:
	// �f�X�g���N�^
	~ObjectsManager()
	{
		Uninit();
	}

	// ����������
	void Init()
	{
		// �I�u�W�F�N�g�̏�����
		for (auto object : objects)
		{
			object->Init();
		}
	}

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

	// �I������
	void Uninit();

	// �I�u�W�F�N�g�̒ǉ�
	template <typename T>
	T* AddObject()
	{
		T* object = NEW T();
		object->Init();
		object->SetCamera(CAMERA_MANAGER.GetNowCamera());
		newObjects.push_back(object);
		return object;
	}

	// �I�u�W�F�N�g�̎擾
	template <typename T>
	T* GetObject()
	{
		for (auto object : objects)
		{
			T* castObject = dynamic_cast<T*>(object);
			if (castObject != nullptr)
			{
				return castObject;
			}
		}
		return nullptr;
	}

private:
	// �I�u�W�F�N�g���\�[�g
	void SortObjects();

private:
	// �I�u�W�F�N�g�̃��X�g
	std::vector<Object*> objects;
	// �X�V���ɒǉ����ꂽ�I�u�W�F�N�g�̃��X�g
	std::vector<Object*> newObjects;

public:	// �V���O���g���֘A

	// �C���X�^���X�̎擾
	static ObjectsManager& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = NEW ObjectsManager();
		}
		return *instance;
	}

	// �C���X�^���X�̔j��
	static void DestroyInstance()
	{
		SAFE_DELETE(instance);
	}

private:
	static inline ObjectsManager* instance = nullptr;
	ObjectsManager() {}
	ObjectsManager(const ObjectsManager& obj) = delete;
	ObjectsManager& operator=(const ObjectsManager& obj) = delete;

};

// �V���O���g���̃C���X�^���X���擾����}�N��
#define OBJECTS_MANAGER ObjectsManager::GetInstance()