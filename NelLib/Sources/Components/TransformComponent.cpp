#include "TransformComponent.h"
#include <Objects/Object.h>

void TransformComponent::Init()
{
}

void TransformComponent::Uninit()
{
}

void TransformComponent::Update()
{
	// ローカル行列の計算
	DirectX::XMFLOAT4 quaternion = m_rotation.GetQuaternion();
	DirectX::XMMATRIX localMatrix = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
		DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&quaternion)) *
		DirectX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z);

	// ローカル行列の取得
	DirectX::XMStoreFloat4x4(&m_localMatrix, localMatrix);

	// ワールド行列の計算
	Object* pParent = GetOwner()->GetParent();
	if (pParent != nullptr)
	{
		// 親のワールド行列の取得
		DirectX::XMFLOAT4X4 parentWorldMatrix = pParent->GetComponent<TransformComponent>()->GetWorldMatrix();
		// ワールド行列の計算
		DirectX::XMMATRIX worldMatrix = localMatrix * DirectX::XMLoadFloat4x4(&parentWorldMatrix);
		// ワールド行列の取得
		DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
	}
	else
	{
		// ワールド行列の計算
		DirectX::XMMATRIX worldMatrix = localMatrix;
		// ワールド行列の取得
		DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
	}
}

DirectX::XMFLOAT4X4 TransformComponent::GetLocalMatrix()
{
	// 転置済みローカル行列の取得
	DirectX::XMFLOAT4X4 localMatrix;
	DirectX::XMStoreFloat4x4(&localMatrix, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m_localMatrix)));
	return localMatrix;
}

DirectX::XMFLOAT4X4 TransformComponent::GetWorldMatrix()
{
	// 転置済みワールド行列の取得
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m_worldMatrix)));
	return worldMatrix;
}

void TransformComponent::translate(VECTOR move)
{
	m_position += move;
}

void TransformComponent::translate(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}

void TransformComponent::rotate(QUATERNION rotate)
{
	m_rotation.rotate(rotate);
}

void TransformComponent::rotate(float x, float y, float z)
{
	// 回転の計算
	QUATERNION rotate(x, y, z);
	m_rotation *= rotate;
}

void TransformComponent::scale(VECTOR scale)
{
	m_scale += scale;
}

void TransformComponent::scale(float x, float y, float z)
{
	m_scale.x += x;
	m_scale.y += y;
	m_scale.z += z;
}
