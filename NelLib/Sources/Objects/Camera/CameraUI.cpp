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

	m_ViewLeft = 0.0f;
	m_ViewRight = width;
	m_ViewTop = 0.0f;
	m_ViewBottom = height;

	// m_ViewLeft = -width / 2.0f;
	// m_ViewRight = width / 2.0f;
	// m_ViewTop = -height / 2.0f;
	// m_ViewBottom = height / 2.0f;


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
	DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&m_view, view);
}

void CameraUI::UpdateProjectionMatrix()
{
	DirectX::XMMATRIX proj = DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(m_ViewLeft, m_ViewRight, m_ViewTop, m_ViewBottom, 0.01f, 100.0f));
	DirectX::XMStoreFloat4x4(&m_projection, proj);
}