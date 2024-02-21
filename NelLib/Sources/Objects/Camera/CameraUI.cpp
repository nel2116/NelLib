#include "CameraUI.h"
#include <DirectX/Renderer.h>

CameraUI::CameraUI()
	: m_ViewLeft(0.0f)
	, m_ViewRight(0.0f)
	, m_ViewTop(0.0f)
	, m_ViewBottom(0.0f)
{
}

void CameraUI::Init()
{
	float height = RENDERER.GetHeight();
	float width = RENDERER.GetWidth();

	// m_ViewLeft = 0.0f;
	// m_ViewRight = width;
	// m_ViewTop = 0.0f;
	// m_ViewBottom = height;

	m_ViewLeft = -width / 2.0f;
	m_ViewRight = width / 2.0f;
	m_ViewBottom = -height / 2.0f;
	m_ViewTop = height / 2.0f;

	m_pTransform->SetPosition(0.0f, 0.0f, -3.0f);

	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void CameraUI::Uninit()
{
}

void CameraUI::Update()
{
}

void CameraUI::UpdateViewMatrix()
{
	// ビュー行列の更新
	DirectX::XMFLOAT3 pos = m_pTransform->GetPosition3();
	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&pos), DirectX::XMLoadFloat3(&m_look), DirectX::XMLoadFloat3(&m_up));
	DirectX::XMStoreFloat4x4(&m_view, DirectX::XMMatrixTranspose(view));
}

void CameraUI::UpdateProjectionMatrix()
{
	// プロジェクション行列の更新
	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(m_ViewLeft, m_ViewRight, m_ViewBottom, m_ViewTop, 0.1f, 1000.0f);
	DirectX::XMStoreFloat4x4(&m_projection, DirectX::XMMatrixTranspose(proj));
	// プロジェクション行列の更新
//	DirectX::XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_near, m_far);
//	DirectX::XMStoreFloat4x4(&m_projection, DirectX::XMMatrixTranspose(projection));
}