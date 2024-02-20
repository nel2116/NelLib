#include "TransformComponent.h"
#include <Objects/Object.h>

TransformComponent::TransformComponent(Object* owner)
	: Component(owner)
	, m_position(Vector3(0.0f, 0.0f, 0.0f))
	, m_rotation(QUATERNION(1.0f, 0.0f, 0.0f, 0.0f))
	, m_scale(Vector3(1.0f, 1.0f, 1.0f))
	, m_localMatrix(DirectX::XMFLOAT4X4())
	, m_worldMatrix(DirectX::XMFLOAT4X4())
{

}


void TransformComponent::Init()
{
}

void TransformComponent::Uninit()
{
}

void TransformComponent::Update()
{
	// クォータニオンでの回転の計算
	DirectX::XMMATRIX localMatrix;
	DirectX::XMMATRIX scaleMatrix = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	DirectX::XMMATRIX rotationMatrix = m_rotation.toMatrix();
	DirectX::XMMATRIX translationMatrix = DirectX::XMMatrixTranslation(m_position.x, m_position.y, m_position.z);

	localMatrix = scaleMatrix * rotationMatrix * translationMatrix;

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

void TransformComponent::translate(Vector3 move)
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
	// 回転の計算
	m_rotation = rotate * m_rotation;
}

void TransformComponent::rotate(float x, float y, float z)
{
	// 回転の計算
	QUATERNION q;

	// クォータニオンの回転
	if (x > 0)
	{
		m_rotation = q.AngleAxis(x, Vector3::right()) * m_rotation;
	}
	else if (x < 0)
	{
		m_rotation = q.AngleAxis(x, Vector3::left()) * m_rotation;
	}
	if (y > 0)
	{
		m_rotation = q.AngleAxis(y, Vector3::up()) * m_rotation;
	}
	else if (y < 0)
	{
		m_rotation = q.AngleAxis(y, Vector3::down()) * m_rotation;
	}
	if (z > 0)
	{
		m_rotation = q.AngleAxis(z, Vector3::forward()) * m_rotation;
	}
	else if (z < 0)
	{
		m_rotation = q.AngleAxis(z, Vector3::back()) * m_rotation;
	}
}

void TransformComponent::scale(Vector3 scale)
{
	m_scale += scale;
}

void TransformComponent::scale(float x, float y, float z)
{
	m_scale.x += x;
	m_scale.y += y;
	m_scale.z += z;
}
