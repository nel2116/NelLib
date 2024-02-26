#pragma once
// ====== �C���N���[�h�� ======
#include <System/Singleton.h>
#include <System/Model.h>
#include <vector>

// ====== �N���X�̐錾 ======
class ModelManager : public Singleton<ModelManager>
{
public:
	enum ModelType
	{
		MODEL_PLAYER,
		MODEL_ENEMY,
		MODEL_STAIRS,

		MODEL_MAX,
	};

public:
	// �f�X�g���N�^
	~ModelManager() { Uninit(); }

	// ������
	void Init();

	// �I��
	void Uninit();

	// ���f���̎擾
	Model* GetModel(ModelType type);

private:
	// ���f���̃��X�g
	std::vector<Model*> m_ModelList;

private:	// �V���O���g���֘A
	friend Singleton<ModelManager>;
	ModelManager() {}

};
// �C���X�^���X���l������}�N��
#define MODEL_MANAGER ModelManager::GetInstance()