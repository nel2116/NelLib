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
	DirectX::XMFLOAT4X4 GetTransposedViewMatrix() const;

	// �]�u�ς݃v���W�F�N�V�����s����擾
	DirectX::XMFLOAT4X4 GetTransposedProjectionMatrix() const;

protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	// �r���[�s��ɕK�v�ȕϐ�
	float m_fov, m_aspect, m_near, m_far;	// �v���W�F�N�V�����s��ɕK�v�ȕϐ�
};

