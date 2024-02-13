#pragma once

// ====== �C���N���[�h�� ======
#include <vector>
#include <Objects/Camera/CameraBase.h>
#include <Objects/Camera/CameraDebug.h>

// ====== �N���X�̒�` ======
class CameraManager
{
public:	// �萔��`
	enum CameraType
	{
		E_CAM_DEBUG,	// �f�o�b�O�J����
		E_CAM_MAX,		// �J�����̍ő吔
	};

public:	// �����o�֐�
	void Init();	// ����������
	void Uninit();	// �I������

	CameraBase* GetCamera(CameraType type);	// �J�����̎擾
	CameraBase* GetNowCamera();	// ���݂̃J�����̎擾
	void SetNowCamera(CameraType type);	// ���݂̃J�����̐ݒ�

private:	// �����o�ϐ�
	// �J�����̃��X�g
	std::vector<CameraBase*> m_Cameras;
	int m_nowCamera;	// ���݂̃J����

public:	// �V���O���g���֘A

	// �C���X�^���X�̎擾
	static CameraManager& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = NEW CameraManager();
		}
		return *instance;
	}

	// �C���X�^���X�̔j��
	static void DestroyInstance()
	{
		SAFE_DELETE(instance);
	}

private:
	static inline CameraManager* instance = nullptr;
	CameraManager() : m_nowCamera(0) {}
	CameraManager(const CameraManager& obj) = delete;
	CameraManager& operator=(const CameraManager& obj) = delete;
};

#define CAMERA_MANAGER CameraManager::GetInstance()	// �V���O���g���C���X�^���X�̎擾�p�}�N��