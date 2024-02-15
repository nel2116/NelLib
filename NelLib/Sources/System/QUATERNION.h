#pragma once
#include"mathUtil.h"
#include"VECTOR.h"
#include <DirectXMath.h>

class QUATERNION
{
public:
	// �R���X�g���N�^
	QUATERNION() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(1.0f) {}
	// �R���X�g���N�^
	QUATERNION(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}
	// �R���X�g���N�^
	QUATERNION(DirectX::XMFLOAT4 quaternion) : m_x(quaternion.x), m_y(quaternion.y), m_z(quaternion.z), m_w(quaternion.w) {}
	// �f�X�g���N�^
	~QUATERNION() {}

	// �Q�b�^�[�A�Z�b�^�[
	// �N�H�[�^�j�I���̐ݒ�
	void SetQuaternion(DirectX::XMFLOAT4 quaternion) { m_x = quaternion.x; m_y = quaternion.y; m_z = quaternion.z; m_w = quaternion.w; }

	// �N�H�[�^�j�I���̐ݒ�
	void SetQuaternion(float x, float y, float z, float w) { m_x = x; m_y = y; m_z = z; m_w = w; }

	// �N�H�[�^�j�I���̐ݒ�
	void SetQuaternion(QUATERNION quaternion) { m_x = quaternion.GetX(); m_y = quaternion.GetY(); m_z = quaternion.GetZ(); m_w = quaternion.GetW(); }

	// �N�H�[�^�j�I���̐ݒ�
	void SetQuaternion(VECTOR axis, float angle);

	// X�̎擾
	float GetX() { return m_x; }
	// X�̐ݒ�
	void SetX(float x) { m_x = x; }
	// Y�̎擾
	float GetY() { return m_y; }
	// Y�̐ݒ�
	void SetY(float y) { m_y = y; }
	// Z�̎擾
	float GetZ() { return m_z; }
	// Z�̐ݒ�
	void SetZ(float z) { m_z = z; }
	// W�̎擾
	float GetW() { return m_w; }
	// W�̐ݒ�
	void SetW(float w) { m_w = w; }

	// ��]�s��̎擾
	DirectX::XMFLOAT4X4 GetRotationMatrix() { return m_rotationMatrix; }

	// ��]����֐�
	void rotate(QUATERNION rotate);

	// ��]����֐�
	void rotate(VECTOR rotate);

	// ��]����֐�
	void rotate(float x, float y, float z);

	// ��]����֐�
	void rotate(VECTOR axis, float angle);

	// leap�֐�
	void lerp(QUATERNION start, QUATERNION end, float t);

	// slerp�֐�
	void slerp(QUATERNION start, QUATERNION end, float t);

	// �N�H�[�^�j�I���̎擾
	DirectX::XMFLOAT4 GetQuaternion() { return DirectX::XMFLOAT4(m_x, m_y, m_z, m_w); }

private:
	// X
	float m_x;
	// Y
	float m_y;
	// Z
	float m_z;
	// W
	float m_w;

	// ��]�s��
	DirectX::XMFLOAT4X4 m_rotationMatrix;
};
