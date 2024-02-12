#include "Object.h"
#include <System/Macro.h>

Object::~Object()
{
	// �R���|�[�l���g�̏I������
	for (auto component : components)
	{
		component->Uninit();
		SAFE_DELETE(component);
	}
	components.clear();
}

void Object::UpdateComponents()
{
	// �V���ɒǉ����ꂽ�R���|�[�l���g��ǉ�
	for (auto newComponent : newComponents)
	{
		components.push_back(newComponent);
	}
	newComponents.clear();

	// �R���|�[�l���g�̃\�[�g
	SortComponents();

	// �R���|�[�l���g�̍X�V
	for (auto component : components)
	{
		// �L���łȂ��͏������΂�
		if (!component->IsEnable()) { continue; }
		component->Update();
	}

	// �j���t���O�������Ă���R���|�[�l���g�̃|�C���^���폜
	auto itr = std::partition(components.begin(), components.end(), [](Component* component) { return component->IsDestroy(); });
	std::for_each(components.begin(), itr, [](Component* component) { SAFE_DELETE(component); });
	components.erase(components.begin(), itr);
}

void Object::DrawComponents()
{
	// �R���|�[�l���g�̕`��
	for (auto component : components)
	{
		// �L���łȂ��͏������΂�
		if (!component->IsEnable()) { continue; }
		component->Draw();
	}
}

void Object::SortComponents()
{
	// �R���|�[�l���g�̃\�[�g
	std::sort(components.begin(), components.end(), [](Component* a, Component* b) { return a->GetOrder() < b->GetOrder(); });
}