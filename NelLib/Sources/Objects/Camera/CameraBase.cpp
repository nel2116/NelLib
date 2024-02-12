#include "CameraBase.h"

#define ASPECT (16.0f / 9.0f)

CameraBase::CameraBase()
	: m_pos(0.0f, 0.0f, -0.3f)
	, m_look(0.0f, 0.0f, 0.0f)
	, m_up(0.0f, 1.0f, 0.0f)
	, m_fov(DirectX::XMConvertToRadians(60))
	, m_aspect(ASPECT)
	, m_near(0.3f)
	, m_far(100.0f)
{
}

DirectX::XMFLOAT4X4 CameraBase::GetTransposedViewMatrix() const
{
	// 転置済みビュー行列を取得
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&m_pos), DirectX::XMLoadFloat3(&m_look), DirectX::XMLoadFloat3(&m_up));
	DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(view));
	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetTransposedProjectionMatrix() const
{
	// 転置済みプロジェクション行列を取得
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	proj = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_near, m_far);
	DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(proj));
	return mat;
}
