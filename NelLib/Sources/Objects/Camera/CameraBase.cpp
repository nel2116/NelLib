#include "CameraBase.h"

#define ASPECT (16.0f / 9.0f)

CameraBase::CameraBase()
	: m_look(0.0f, 0.0f, 0.0f)
	, m_up(0.0f, 1.0f, 0.0f)
	, m_fov(DirectX::XMConvertToRadians(60))
	, m_aspect(ASPECT)
	, m_near(0.3f)
	, m_far(100.0f)
{
	m_pTransform->SetPosition(0.0f, 0.0f, -0.3f);
}

DirectX::XMFLOAT4X4 CameraBase::GetTransposedViewMatrix()
{
	UpdateViewMatrix();
	DirectX::XMFLOAT4X4 view;
	DirectX::XMStoreFloat4x4(&view, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m_view)));
	return view;
}

DirectX::XMFLOAT4X4 CameraBase::GetTransposedProjectionMatrix()
{
	UpdateProjectionMatrix();
	DirectX::XMFLOAT4X4 projection;
	DirectX::XMStoreFloat4x4(&projection, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m_projection)));
	return projection;
}

void CameraBase::UpdateViewMatrix()
{
	// ビュー行列の更新
	DirectX::XMFLOAT3 pos = m_pTransform->GetPosition3();
	DirectX::XMStoreFloat4x4(&m_view, DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&pos), DirectX::XMLoadFloat3(&m_look), DirectX::XMLoadFloat3(&m_up)));
}

void CameraBase::UpdateProjectionMatrix()
{
	// プロジェクション行列の更新
	DirectX::XMStoreFloat4x4(&m_projection, DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_near, m_far));
}
