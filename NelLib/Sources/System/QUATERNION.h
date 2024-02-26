#pragma once
#include <cmath>
#include <DirectXMath.h>
#include"mathUtil.h"
#include"VECTOR.h"

#define PI 3.1415926f

class QUATERNION
{
public:
	// �����o�ϐ�
	float w; // ������
	float x; // ��������x����
	float y; // ��������y����
	float z; // ��������z����

	// �R���X�g���N�^
	QUATERNION(); // �f�t�H���g�R���X�g���N�^
	QUATERNION(float x, float y, float z, float w); // �����t���R���X�g���N�^
	QUATERNION(const QUATERNION& q); // �R�s�[�R���X�g���N�^


	// �f�X�g���N�^
	~QUATERNION();

	// ������Z�q
	QUATERNION& operator=(const QUATERNION& q);
	QUATERNION& operator=(const DirectX::XMVECTOR& v);

	// �P�����Z�q
	QUATERNION operator-() const; // �������]
	QUATERNION operator~() const; // ����

	// �񍀉��Z�q
	QUATERNION operator+(const QUATERNION& q) const; // ���Z
	QUATERNION operator+(float s) const; // �X�J���[���Z
	QUATERNION operator-(const QUATERNION& q) const; // ���Z
	QUATERNION operator-(float s) const; // �X�J���[���Z
	QUATERNION operator*(const QUATERNION& q) const; // ��Z
	QUATERNION operator*(float s) const; // �X�J���[��Z
	QUATERNION operator/(const QUATERNION& q) const; // ���Z
	QUATERNION operator/(float s) const; // �X�J���[���Z

	// ������Z�q
	QUATERNION& operator+=(const QUATERNION& q); // ���Z
	QUATERNION& operator+=(float s); // �X�J���[���Z
	QUATERNION& operator-=(const QUATERNION& q); // ���Z
	QUATERNION& operator-=(float s); // �X�J���[���Z
	QUATERNION& operator*=(const QUATERNION& q); // ��Z
	QUATERNION& operator*=(float s); // �X�J���[��Z
	QUATERNION& operator/=(const QUATERNION& q); // ���Z
	QUATERNION& operator/=(float s); // �X�J���[���Z

	// ���̑��̉��Z�q	
	QUATERNION operator*(const Vector3& v) const; // ��Z
	QUATERNION operator/(const Vector3& v) const; // ���Z

	// �����o�֐�
	float magnitude() const; // �m�����i�傫���j��Ԃ�
	QUATERNION normalize() const; // ���K�������N�H�[�^�j�I����Ԃ�
	QUATERNION inverse() const; // �t���̃N�H�[�^�j�I����Ԃ�
	float dot(const QUATERNION& q) const; // ���ς�Ԃ�
	QUATERNION cross(const QUATERNION& q) const; // �O�ς�Ԃ�
	QUATERNION slerp(const QUATERNION& q, float t) const; // ���ʐ��`��Ԃ�Ԃ�
	QUATERNION lerp(const QUATERNION& q, float t) const; // ���`��Ԃ�Ԃ�
	DirectX::XMVECTOR toXMVECTOR() const; // �N�H�[�^�j�I����XMVECTOR�ɕϊ����ĕԂ�
	DirectX::XMMATRIX toMatrix() const; // �N�H�[�^�j�I�����s��ɕϊ����ĕԂ�
	DirectX::XMMATRIX toMatrixTranspose() const; // �N�H�[�^�j�I�����s��ɕϊ����ĕԂ�
	DirectX::XMMATRIX toMatrixInverse() const; // �N�H�[�^�j�I�����s��ɕϊ����ĕԂ�
	DirectX::XMFLOAT4 toFloat4() const; // �N�H�[�^�j�I����XMFLOAT4�ɕϊ����ĕԂ�
	DirectX::XMFLOAT4X4 toFloat4x4() const; // �N�H�[�^�j�I����XMFLOAT4X4�ɕϊ����ĕԂ�

	// �N�H�[�^�j�I���̐���
	QUATERNION AngleAxis(float angle, Vector3 axis) const;// �����̉�]��\���N�H�[�^�j�I���𐶐����ĕԂ�

	// �ÓI�����o�֐�
	// �N�H�[�^�j�I���̐���
	static QUATERNION createIdentity(); // �P�ʃN�H�[�^�j�I���𐶐����ĕԂ�
};
