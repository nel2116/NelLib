#pragma once

// ====== �C���N���[�h�� ======
#include <Objects/Camera/CameraBase.h>

// ====== �O���錾 ======

// ====== �N���X�錾 ======
class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug();

	void Update() override;

	void Uninit() override {}

private:
	// ====== �����o�ϐ� ======
	float m_radXZ;
	float m_radY;
	float m_distance;

};