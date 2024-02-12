#include "ObjectsManager.h"

void ObjectsManager::Update()
{
	// �V���ɒǉ����ꂽ�I�u�W�F�N�g��ǉ�
	for (auto newObject : newObjects)
	{
		objects.push_back(newObject);
	}
	newObjects.clear();

	// �I�u�W�F�N�g�̃\�[�g
	SortObjects();

	// �I�u�W�F�N�g�̍X�V
	for (auto object : objects)
	{
		// �L���łȂ��͏������΂�
		if (!object->IsEnable()) { continue; }
		object->Update();
	}
	// �j���t���O�������Ă���I�u�W�F�N�g���폜
	auto itr = std::partition(objects.begin(), objects.end(), [](Object* object) { return object->IsDestroy(); });
	std::for_each(objects.begin(), itr, [](Object* object) { delete object; });
	objects.erase(objects.begin(), itr);
}

void ObjectsManager::Draw()
{
	// �I�u�W�F�N�g�̕`��
	for (auto object : objects)
	{
		// �L���łȂ��͏������΂�
		if (!object->IsEnable()) { continue; }
		object->Draw();
	}
}

void ObjectsManager::Uninit()
{
	// �I�u�W�F�N�g�̏I������
	for (auto object : objects)
	{
		object->Uninit();
		SAFE_DELETE(object);
	}
	objects.clear();
}

void ObjectsManager::SortObjects()
{
	// �I�u�W�F�N�g�̃\�[�g
	std::sort(objects.begin(), objects.end(),
		[](Object* a, Object* b) { return a->GetOrder() < b->GetOrder(); });
}
