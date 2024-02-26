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
	// クォータニオンの除算は、クォータニオンの逆数を求めて乗算する
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
	// クォータニオンとベクトルの乗算は、クォータニオンをベクトルに変換してからクォータニオンとベクトルの乗算を行う
	QUATERNION q(0.0f, v.x, v.y, v.z);
	return *this * q;
}

QUATERNION QUATERNION::operator/(const Vector3& v) const
{
	// クォータニオンとベクトルの除算は、クォータニオンをベクトルに変換してからクォータニオンとベクトルの除算を行う
	QUATERNION q(0.0f, v.x, v.y, v.z);
	return *this / q;
}

float QUATERNION::magnitude() const
{
	// クォータニオンのマグニチュードは、クォータニオンの大きさを求める
	return sqrtf(w * w + x * x + y * y + z * z);
}

QUATERNION QUATERNION::normalize() const
{
	// クォータニオンの正規化は、クォータニオンを単位クォータニオンに変換する
	float m = magnitude();
	return QUATERNION(w / m, x / m, y / m, z / m);
}

QUATERNION QUATERNION::inverse() const
{
	// クォータニオンの逆数は、クォータニオンの共役を求めてからクォータニオンの大きさの二乗で割る
	float m = magnitude();
	return QUATERNION(w / (m * m), -x / (m * m), -y / (m * m), -z / (m * m));
}

float QUATERNION::dot(const QUATERNION& q) const
{
	// クォータニオンのドット積は、クォータニオン同士の内積を求める
	return w * q.w + x * q.x + y * q.y + z * q.z;
}

QUATERNION QUATERNION::cross(const QUATERNION& q) const
{
	// クォータニオンのクロス積は、クォータニオン同士の外積を求める
	return QUATERNION(
		w * q.w - x * q.x - y * q.y - z * q.z,
		w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x,
		w * q.z + x * q.y - y * q.x + z * q.w
	);
}

QUATERNION QUATERNION::slerp(const QUATERNION& q, float t) const
{
	// 線形補間
	float qr = dot(q);
	float theta = acosf(qr);
	float s0 = sinf(((1.0f - t) * theta) / sin(theta));
	float s1 = sin(t * theta) / sin(theta);

	return *this * s0 + q * s1;
}

QUATERNION QUATERNION::lerp(const QUATERNION& q, float t) const
{
	// クォータニオンの線形補間は、クォータニオン同士の線形補間を求める
	return *this * (1.0f - t) + q * t;
}

DirectX::XMVECTOR QUATERNION::toXMVECTOR() const
{
	return DirectX::XMVectorSet(x, y, z, w);
}

DirectX::XMMATRIX QUATERNION::toMatrix() const
{
	// クォータニオンから行列に変換する
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
	// 角度をラジアンに変換
	angle = DEG2RAD(angle);

	// 回転軸の長さを正規化
	axis = axis.normalize();

	// 回転角度の半分
	float halfAngle = angle / 2.0f;

	// sin と cos を計算
	float sinHalfAngle = sin(halfAngle);
	float cosHalfAngle = cos(halfAngle);

	// クォータニオンの各成分を計算
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
