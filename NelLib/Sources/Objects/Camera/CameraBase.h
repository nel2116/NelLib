#pragma once
#include <Objects/Object.h>
#include <DirectXMath.h>

class CameraBase : public Object
{
public:
	CameraBase();
	~CameraBase() {}

	virtual void Update() override {}

	virtual void Uninit() override {}

	// �]�u�ς݃r���[�s����擾
	virtual DirectX::XMFLOAT4X4 GetViewMatrix();

	// �]�u�ς݃v���W�F�N�V�����s����擾
	virtual DirectX::XMFLOAT4X4 GetProjectionMatrix();

protected:
	// �r���[�s����X�V
	virtual void UpdateViewMatrix();
	// �v���W�F�N�V�����s����X�V
	virtual void UpdateProjectionMatrix();

	DirectX::XMFLOAT3 m_look, m_up;	// �r���[�s��ɕK�v�ȕϐ�
	float m_fov, m_aspect, m_near, m_far;	// �v���W�F�N�V�����s��ɕK�v�ȕϐ�
	DirectX::XMFLOAT4X4 m_view, m_projection;	// �r���[�s��A�v���W�F�N�V�����s��
};

