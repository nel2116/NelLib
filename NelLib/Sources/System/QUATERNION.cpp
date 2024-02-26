#include "QUATERNION.h"
#include "Macro.h"

QUATERNION::QUATERNION()
	: w(1.0f), x(0.0f), y(0.0f), z(0.0f)
{}

QUATERNION::QUATERNION(float w, float x, float y, float z)
	: w(w), x(x), y(y), z(z)
{}

QUATERNION::QUATERNION(const QUATERNION& q)
	: w(q.w), x(q.x), y(q.y), z(q.z)
{}

QUATERNION::~QUATERNION()
{
}

QUATERNION& QUATERNION::operator=(const QUATERNION& q)
{
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}

QUATERNION& QUATERNION::operator=(const DirectX::XMVECTOR& v)
{
	w = DirectX::XMVectorGetW(v);
	x = DirectX::XMVectorGetX(v);
	y = DirectX::XMVectorGetY(v);
	z = DirectX::XMVectorGetZ(v);
	return *this;
}

QUATERNION QUATERNION::operator-() const
{
	return QUATERNION(-w, -x, -y, -z);
}

QUATERNION QUATERNION::operator~() const
{
	return QUATERNION(w, -x, -y, -z);
}

QUATERNION QUATERNION::operator+(const QUATERNION& q) const
{
	return QUATERNION(w + q.w, x + q.x, y + q.y, z + q.z);
}

QUATERNION QUATERNION::operator+(float s) const
{
	return QUATERNION(w + s, x, y, z);
}

QUATERNION QUATERNION::operator-(const QUATERNION& q) const
{
	return QUATERNION(w - q.w, x - q.x, y - q.y, z - q.z);
}

QUATERNION QUATERNION::operator-(float s) const
{
	return QUATERNION(w - s, x, y, z);
}

QUATERNION QUATERNION::operator*(const QUATERNION& q) const
{
	return QUATERNION(
		w * q.w - x * q.x - y * q.y - z * q.z,
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w
	);
}

QUATERNION QUATERNION::operator*(float s) const
{
	return QUATERNION(w * s, x * s, y * s, z * s);
}

QUATERNION QUATERNION::operator/(const QUATERNION& q) const
{
	// �N�H�[�^�j�I���̏��Z�́A�N�H�[�^�j�I���̋t�������߂ď�Z����
	return *this * q.inverse();
}

QUATERNION QUATERNION::operator/(float s) const
{
	return QUATERNION(w / s, x / s, y / s, z / s);
}

QUATERNION& QUATERNION::operator+=(const QUATERNION& q)
{
	w += q.w;
	x += q.x;
	y += q.y;
	z += q.z;
	return *this;
}

QUATERNION& QUATERNION::operator+=(float s)
{
	w += s;
	return *this;
}

QUATERNION& QUATERNION::operator-=(const QUATERNION& q)
{
	w -= q.w;
	x -= q.x;
	y -= q.y;
	z -= q.z;
	return *this;
}

QUATERNION& QUATERNION::operator-=(float s)
{
	w -= s;
	return *this;
}

QUATERNION& QUATERNION::operator*=(const QUATERNION& q)
{
	*this = *this * q;
	return *this;
}

QUATERNION& QUATERNION::operator*=(float s)
{
	w *= s;
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

QUATERNION& QUATERNION::operator/=(const QUATERNION& q)
{
	*this = *this * q.inverse();
	return *this;
}

QUATERNION& QUATERNION::operator/=(float s)
{
	w /= s;
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

QUATERNION QUATERNION::operator*(const Vector3& v) const
{
	// �N�H�[�^�j�I���ƃx�N�g���̏�Z�́A�N�H�[�^�j�I�����x�N�g���ɕϊ����Ă���N�H�[�^�j�I���ƃx�N�g���̏�Z���s��
	QUATERNION q(0.0f, v.x, v.y, v.z);
	return *this * q;
}

QUATERNION QUATERNION::operator/(const Vector3& v) const
{
	// �N�H�[�^�j�I���ƃx�N�g���̏��Z�́A�N�H�[�^�j�I�����x�N�g���ɕϊ����Ă���N�H�[�^�j�I���ƃx�N�g���̏��Z���s��
	QUATERNION q(0.0f, v.x, v.y, v.z);
	return *this / q;
}

float QUATERNION::magnitude() const
{
	// �N�H�[�^�j�I���̃}�O�j�`���[�h�́A�N�H�[�^�j�I���̑傫�������߂�
	return sqrtf(w * w + x * x + y * y + z * z);
}

QUATERNION QUATERNION::normalize() const
{
	// �N�H�[�^�j�I���̐��K���́A�N�H�[�^�j�I����P�ʃN�H�[�^�j�I���ɕϊ�����
	float m = magnitude();
	return QUATERNION(w / m, x / m, y / m, z / m);
}

QUATERNION QUATERNION::inverse() const
{
	// �N�H�[�^�j�I���̋t���́A�N�H�[�^�j�I���̋��������߂Ă���N�H�[�^�j�I���̑傫���̓��Ŋ���
	float m = magnitude();
	return QUATERNION(w / (m * m), -x / (m * m), -y / (m * m), -z / (m * m));
}

float QUATERNION::dot(const QUATERNION& q) const
{
	// �N�H�[�^�j�I���̃h�b�g�ς́A�N�H�[�^�j�I�����m�̓��ς����߂�
	return w * q.w + x * q.x + y * q.y + z * q.z;
}

QUATERNION QUATERNION::cross(const QUATERNION& q) const
{
	// �N�H�[�^�j�I���̃N���X�ς́A�N�H�[�^�j�I�����m�̊O�ς����߂�
	return QUATERNION(
		w * q.w - x * q.x - y * q.y - z * q.z,
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w
	);
}

QUATERNION QUATERNION::slerp(const QUATERNION& q, float t) const
{
	// ���`���
	float qr = dot(q);
	float theta = acosf(qr);
	float s0 = sinf(((1.0f - t) * theta) / sin(theta));
	float s1 = sin(t * theta) / sin(theta);

	return *this * s0 + q * s1;
}

QUATERNION QUATERNION::lerp(const QUATERNION& q, float t) const
{
	// �N�H�[�^�j�I���̐��`��Ԃ́A�N�H�[�^�j�I�����m�̐��`��Ԃ����߂�
	return *this * (1.0f - t) + q * t;
}

DirectX::XMVECTOR QUATERNION::toXMVECTOR() const
{
	return DirectX::XMVectorSet(x, y, z, w);
}

DirectX::XMMATRIX QUATERNION::toMatrix() const
{
	// �N�H�[�^�j�I������s��ɕϊ�����
	return DirectX::XMMatrixRotationQuaternion(this->toXMVECTOR());
}

DirectX::XMMATRIX QUATERNION::toMatrixTranspose() const
{
	DirectX::XMMATRIX m = this->toMatrix();
	return DirectX::XMMatrixTranspose(m);
}

DirectX::XMMATRIX QUATERNION::toMatrixInverse() const
{
	DirectX::XMMATRIX m = this->toMatrix();
	return DirectX::XMMatrixInverse(nullptr, m);
}

DirectX::XMFLOAT4 QUATERNION::toFloat4() const
{
	return DirectX::XMFLOAT4(w, x, y, z);
}

DirectX::XMFLOAT4X4 QUATERNION::toFloat4x4() const
{
	DirectX::XMMATRIX m = this->toMatrix();
	DirectX::XMFLOAT4X4 f;
	DirectX::XMStoreFloat4x4(&f, m);
	return f;
}

QUATERNION QUATERNION::AngleAxis(float angle, Vector3 axis) const
{
	// �p�x�����W�A���ɕϊ�
	angle = DEG2RAD(angle);

	// ��]���̒����𐳋K��
	axis = axis.normalize();

	// ��]�p�x�̔���
	float halfAngle = angle / 2.0f;

	// sin �� cos ���v�Z
	float sinHalfAngle = sin(halfAngle);
	float cosHalfAngle = cos(halfAngle);

	// �N�H�[�^�j�I���̊e�������v�Z
	QUATERNION q;
	q.x = axis.x * sinHalfAngle;
	q.y = axis.y * sinHalfAngle;
	q.z = axis.z * sinHalfAngle;
	q.w = cosHalfAngle;

	return q;
}

QUATERNION QUATERNION::createIdentity()
{
	return QUATERNION(1.0f, 0.0f, 0.0f, 0.0f);
}
