#pragma once

// ====== �C���N���[�h�� ======
#include <vector>
#include <System/Singleton.h>
#include <Objects/Camera/CameraBase.h>

// ====== �N���X�̒�` ======
class CameraManager : public Singleton<CameraManager>
{
public:	// �萔��`
	enum CameraType
	{
		E_CAM_DEBUG,	// �f�o�b�O�J����
		E_CAM_UI,		// UI�J����
		E_CAM_MAX,		// �J�����̍ő吔
	};

public:	// �����o�֐�
	~CameraManager() { Uninit(); }	// �f�X�g���N�^
	void Init();	// ����������
	void Uninit();	// �I������

	CameraBase* GetCamera(CameraType type);	// �J�����̎擾
	CameraBase* GetNowCamera();	// ���݂̃J�����̎擾
	void SetNowCamera(CameraType type);	// ���݂̃J�����̐ݒ�

private:	// �����o�ϐ�
	// �J�����̃��X�g
	std::vector<CameraBase*> m_Cameras;
	int m_nowCamera;	// ���݂̃J����

private:	// �V���O���g���֘A
	friend Singleton<CameraManager>;
	CameraManager() : m_nowCamera(0) {}
};

// �J�����}�l�[�W���̃C���X�^���X�̎擾
#define CAMERA_MANAGER CameraManager::GetInstance()