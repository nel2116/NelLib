#include "QUATERNION.h"

void QUATERNION::rotate(QUATERNION rotate)
{
	// 回転行列の計算
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&rotate));
	// 回転行列の取得
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::rotate(VECTOR rotate)
{
	// 回転行列の計算
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotate.x, rotate.y, rotate.z);
	// 回転行列の取得
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::rotate(float x, float y, float z)
{
	// 引数の角度をラジアンに変換
	x = DirectX::XMConvertToRadians(x);
	y = DirectX::XMConvertToRadians(y);
	z = DirectX::XMConvertToRadians(z);
	// 回転行列の計算
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(x, y, z);
	// 回転行列の取得
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::rotate(VECTOR axis, float angle)
{
	// 回転行列の計算
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&axis), angle);
	// 回転行列の取得
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::lerp(QUATERNION start, QUATERNION end, float t)
{
	// 回転行列の計算
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionSlerp(DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&start), DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&end), t));
	// 回転行列の取得
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::slerp(QUATERNION start, QUATERNION end, float t)
{
	// 回転行列の計算
	DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionSlerp(DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&start), DirectX::XMLoadFloat4((DirectX::XMFLOAT4*)&end), t));
	// 回転行列の取得
	DirectX::XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);
}

void QUATERNION::SetQuaternion(VECTOR axis, float angle)
{
	// クォータニオンの計算
	DirectX::XMVECTOR quaternion = DirectX::XMQuaternionRotationAxis(DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&axis), angle);
	// クォータニオンの取得
	DirectX::XMStoreFloat4((DirectX::XMFLOAT4*)&quaternion, quaternion);
	// クォータニオンの設定
	m_x = quaternion.m128_f32[0];
	m_y = quaternion.m128_f32[1];
	m_z = quaternion.m128_f32[2];
	m_w = quaternion.m128_f32[3];
}

