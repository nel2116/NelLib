#include "ModelManager.h"

void ModelManager::Init()
{
	for (int i = 0; i < MODEL_MAX; ++i)
	{
		m_ModelList.push_back(NEW Model());
	}

	m_ModelList[MODEL_PLAYER]->Load("Assets/Models/eyeBat/eyebat.fbx");
	m_ModelList[MODEL_ENEMY]->Load("Assets/Models/eyeBat/eyebat.fbx");
	m_ModelList[MODEL_STAIRS]->Load("Assets/Models/stairs/stairs.fbx", 5.0f);

}

void ModelManager::Uninit()
{
	for (auto model : m_ModelList)
	{
		SAFE_DELETE(model);
	}
	m_ModelList.clear();
}

Model* ModelManager::GetModel(ModelType type)
{
	return m_ModelList[type];
}
