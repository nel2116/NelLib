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

DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix()
{
	UpdateViewMatrix();
	return m_view;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	UpdateProjectionMatrix();
	return m_projection;
}

void CameraBase::UpdateViewMatrix()
{
	// ビュー行列の更新
	DirectX::XMFLOAT3 look = m_look.toXMFLOAT3();
	DirectX::XMFLOAT3 up = m_up.toXMFLOAT3();
	DirectX::XMFLOAT3 pos = m_pTransform->GetPosition3();
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&pos), DirectX::XMLoadFloat3(&look), DirectX::XMLoadFloat3(&up));
	DirectX::XMStoreFloat4x4(&m_view, DirectX::XMMatrixTranspose(view));
}

void CameraBase::UpdateProjectionMatrix()
{
	// プロジェクション行列の更新
	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_near, m_far);
	DirectX::XMStoreFloat4x4(&m_projection, DirectX::XMMatrixTranspose(projection));
}
