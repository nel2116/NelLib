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
	// ���[�J���s��̌v�Z
	DirectX::XMFLOAT4 quaternion = m_rotation.GetQuaternion();
	DirectX::XMMATRIX localMatrix = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) *
		DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&quaternion)) *
		DirectX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z);

	// ���[�J���s��̎擾
	DirectX::XMStoreFloat4x4(&m_localMatrix, localMatrix);

	// ���[���h�s��̌v�Z
	Object* pParent = GetOwner()->GetParent();
	if (pParent != nullptr)
	{
		// �e�̃��[���h�s��̎擾
		DirectX::XMFLOAT4X4 parentWorldMatrix = pParent->GetComponent<TransformComponent>()->GetWorldMatrix();
		// ���[���h�s��̌v�Z
		DirectX::XMMATRIX worldMatrix = localMatrix * DirectX::XMLoadFloat4x4(&parentWorldMatrix);
		// ���[���h�s��̎擾
		DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
	}
	else
	{
		// ���[���h�s��̌v�Z
		DirectX::XMMATRIX worldMatrix = localMatrix;
		// ���[���h�s��̎擾
		DirectX::XMStoreFloat4x4(&m_worldMatrix, worldMatrix);
	}
}

DirectX::XMFLOAT4X4 TransformComponent::GetLocalMatrix()
{
	// �]�u�ς݃��[�J���s��̎擾
	DirectX::XMFLOAT4X4 localMatrix;
	DirectX::XMStoreFloat4x4(&localMatrix, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m_localMatrix)));
	return localMatrix;
}

DirectX::XMFLOAT4X4 TransformComponent::GetWorldMatrix()
{
	// �]�u�ς݃��[���h�s��̎擾
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
	// ��]�̌v�Z
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
