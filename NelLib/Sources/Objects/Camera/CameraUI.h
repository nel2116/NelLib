#pragma once

#include "CameraBase.h"

// ====== �N���X�̐錾 ======
class CameraUI : public CameraBase
{

public:
	// �R���X�g���N�^
	CameraUI();
	// �f�X�g���N�^
	~CameraUI() {}

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;
protected:
	// �r���[�s����X�V
	void UpdateViewMatrix() override;

	// �v���W�F�N�V�����s����X�V
	void UpdateProjectionMatrix() override;

private:
	float m_ViewLeft, m_ViewRight, m_ViewTop, m_ViewBottom;
};