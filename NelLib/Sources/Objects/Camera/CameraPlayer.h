#pragma once
// ====== �C���N���[�h�� ======
#include <Objects/Camera/CameraBase.h>

// ====== �N���X�錾 ======
class CameraPlayer : public CameraBase
{
public:
	// �R���X�g���N�^
	CameraPlayer();
	// �f�X�g���N�^
	~CameraPlayer() {}

	void Update() override;

	void Uninit() override {}

private:
	// ====== �����o�ϐ� ======
	float m_radXZ;
	float m_radY;
	float m_distance;
};