#pragma once

// ====== �C���N���[�h�� ======
#include <windows.h>
#include <typeinfo>
#include <vector>
#include <Objects/Object.h>
#include <System/Macro.h>
#include <System/Singleton.h>
#include "CameraManager.h"

// ====== �O���錾 ======

// ====== �N���X�̐錾 ======
class ObjectsManager : public Singleton<ObjectsManager>
{
public:
	// �f�X�g���N�^
	~ObjectsManager() { Uninit(); }

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
	T* AddObjects()
	{
		T* object = nullptr;
		// Object�N���X���p�����Ă��Ȃ��N���X�͒ǉ��ł��Ȃ�
		if (!typeid(T).before(typeid(Object*)))
		{
			// �G���[���b�Z�[�W��\��
			//typeid����^�����擾���ăG���[�Ƃ��ďo�͂���
			std::string typeName = typeid(T).name();
			std::string error = "�G���[: " + typeName + " ��Object�N���X���p�����Ă��܂���B";
			OutputDebugStringA(error.c_str());
			return object;
		}
		object = NEW T();
		newObjects.push_back(object);
		return object;
	}

	// �I�u�W�F�N�g�̎擾
	template <typename T>
	T* GetObjects()
	{
		for (auto object : objects)
		{
			T* castObject = dynamic_cast<T*>(object);
			if (castObject != nullptr)
			{
				return castObject;
			}
		}
		// ������Ȃ������ꍇ�͒ǉ��\��̃I�u�W�F�N�g������
		for (auto object : newObjects)
		{
			T* castObject = dynamic_cast<T*>(object);
			if (castObject != nullptr)
			{
				return castObject;
			}
		}
		// ����ł�������Ȃ������ꍇ��nullptr��Ԃ�
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
	friend Singleton<ObjectsManager>;
	ObjectsManager() {}
};

// �V���O���g���̃C���X�^���X���擾����}�N��
#define OBJECTS_MANAGER ObjectsManager::GetInstance()