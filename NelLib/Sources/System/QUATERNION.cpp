#include "QUATERNION.h"

void QUATERNION::rotate(QUATERNION rotate)
{
	// ��]�s��̌v�Z
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&rotate));
	// ��]�s��̎擾
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::rotate(VECTOR rotate)
{
	// ��]�s��̌v�Z
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotate.x, rotate.y, rotate.z);
	// ��]�s��̎擾
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::rotate(float x, float y, float z)
{
	// �����̊p�x�����W�A���ɕϊ�
	x = DirectX::XMConvertToRadians(x);
	y = DirectX::XMConvertToRadians(y);
	z = DirectX::XMConvertToRadians(z);
	// ��]�s��̌v�Z
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(x, y, z);
	// ��]�s��̎擾
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::rotate(VECTOR axis, float angle)
{
	// ��]�s��̌v�Z
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&axis), angle);
	// ��]�s��̎擾
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::lerp(QUATERNION start, QUATERNION end, float t)
{
	// ��]�s��̌v�Z
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionSlerp(DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&start), DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&end), t));
	// ��]�s��̎擾
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::slerp(QUATERNION start, QUATERNION end, float t)
{
	// ��]�s��̌v�Z
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionSlerp(DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&start), DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&end), t));
	// ��]�s��̎擾
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::SetQuaternion(VECTOR axis, float angle)
{
	// �N�H�[�^�j�I���̌v�Z
	DirectX::XMVECTOR quaternion = DirectX::XMQuaternionRotationAxis(DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&axis), angle);
	// �N�H�[�^�j�I���̎擾
	DirectX::XMStoreFloat4((DirectX::XMFLOAT4*)&quaternion, quaternion);
	// �N�H�[�^�j�I���̐ݒ�
	m_x = quaternion.m128_f32[0];
	m_y = quaternion.m128_f32[1];
	m_z = quaternion.m128_f32[2];
	m_w = quaternion.m128_f32[3];
}

