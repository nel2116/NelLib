#include <math.h>
#include "VECTOR.h"

#define EPSILON 0.00001f

// ３次元ベクトルの一般関数-------------------------------------------------------
Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

void Vector3::set(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator+(const float f) const
{
	return Vector3(x + f, y + f, z + f);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator-(const float f) const
{
	return Vector3(x - f, y - f, z - f);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator*(float f) const
{
	return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator/(const Vector3& v) const
{
	return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector3 Vector3::operator/(float f) const
{
	return Vector3(x / f, y / f, z / f);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

bool Vector3::operator==(const Vector3& v) const
{
	// 誤差を許容する
	return fabs(x - v.x) < EPSILON && fabs(y - v.y) < EPSILON && fabs(z - v.z) < EPSILON;
}

bool Vector3::operator!=(const Vector3& v) const
{
	// 誤差を許容する
	return fabs(x - v.x) >= EPSILON || fabs(y - v.y) >= EPSILON || fabs(z - v.z) >= EPSILON;
}

void Vector3::operator=(const Vector3& v)
{
	this->x = v.x; this->y = v.y; this->z = v.z;
}

void Vector3::operator=(const float f)
{
	this->x = f; this->y = f; this->z = f;
}

void Vector3::operator+=(const Vector3& v)
{
	x += v.x; y += v.y; z += v.z;
}

void Vector3::operator+=(const float f)
{
	x += f; y += f; z += f;
}

void Vector3::operator-=(const Vector3& v)
{
	x -= v.x; y -= v.y; z -= v.z;
}

void Vector3::operator-=(const float f)
{
	x -= f; y -= f; z -= f;
}

void Vector3::operator*=(float f)
{
	x *= f; y *= f; z *= f;
}

void Vector3::operator*=(const Vector3& v)
{
	x *= v.x; y *= v.y; z *= v.z;
}

void Vector3::operator/=(float f)
{
	x /= f; y /= f; z /= f;
}

void Vector3::operator/=(const Vector3& v)
{
	x /= v.x; y /= v.y; z /= v.z;
}

DirectX::XMFLOAT3 Vector3::toXMFLOAT3() const
{
	return DirectX::XMFLOAT3(x, y, z);
}

DirectX::XMVECTOR Vector3::toXMVECTOR() const
{
	return DirectX::XMVectorSet(x, y, z, 0.0f);
}

float Vector3::sqMag() const
{
	return x * x + y * y + z * z;
}

float Vector3::magSq() const
{
	return x * x + y * y + z * z;
}

float Vector3::mag() const
{
	return sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::setMag(float mag)
{
	// ３次元ベクトルの長さを設定
	float len = sqrtf(x * x + y * y + z * z);
	if (len > 0) {
		mag /= len;
		x *= mag;
		y *= mag;
		z *= mag;
	}
	return Vector3(x, y, z);
}

Vector3 Vector3::limmit(float maxMag)
{
	// ３次元ベクトルの長さを制限
	float len = sqrtf(x * x + y * y + z * z);
	if (len > maxMag) {
		maxMag /= len;
		x *= maxMag;
		y *= maxMag;
		z *= maxMag;
	}
	return Vector3(x, y, z);
}

Vector3 Vector3::normalize()
{
	float len = sqrtf(x * x + y * y + z * z);
	if (len > 0) {
		x /= len;
		y /= len;
		z /= len;
	}
	return Vector3(x, y, z);
}

Vector3 Vector3::lerp(const Vector3& v, float t) const
{
	// leap
	return Vector3(
		x + (v.x - x) * t,
		y + (v.y - y) * t,
		z + (v.z - z) * t
	);
}

float Vector3::dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v) const
{
	return Vector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}

float Vector3::crossZ(const Vector3& v) const
{
	return x * v.y - y * v.x;
}

float Vector3::crossY(const Vector3& v) const
{
	return x * v.z - z * v.x;
}

Vector3 Vector3::zero()
{
	return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3 Vector3::one()
{
	return Vector3(1.0f, 1.0f, 1.0f);
}

Vector3 Vector3::right()
{
	return Vector3(1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::up()
{
	return Vector3(0.0f, 1.0f, 0.0f);
}

Vector3 Vector3::forward()
{
	return Vector3(0.0f, 0.0f, 1.0f);
}

Vector3 Vector3::left()
{
	return Vector3(-1.0f, 0.0f, 0.0f);
}

Vector3 Vector3::down()
{
	return Vector3(0.0f, -1.0f, 0.0f);
}

Vector3 Vector3::back()
{
	return Vector3(0.0f, 0.0f, -1.0f);
}

Vector2 operator*(float f, const Vector2& v)
{
	// ２次元ベクトルとスカラーの乗算
	return Vector2(f * v.x, f * v.y);
}

Vector2 normalize(const Vector2& a)
{
	// ２次元ベクトルの正規化
	float l = sqrtf(a.x * a.x + a.y * a.y);
	if (l > 0) {
		return Vector2(a.x / l, a.y / l);
	}
	return a;
}

float dot(const Vector2& a, const Vector2& b)
{
	// ２次元ベクトルの内積
	return a.x * b.x + a.y * b.y;
}

float cross(const Vector2& a, const Vector2& b)
{
	// ２次元ベクトルの外積
	return a.x * b.y - a.y * b.x;
}

float crossY(const Vector2& a, const Vector2& b)
{
	// ２次元ベクトルの外積
	return a.x * b.y - a.y * b.x;
}

Vector3 operator*(float f, const Vector3& v)
{
	return Vector3(f * v.x, f * v.y, f * v.z);
}

Vector3 normalize(const Vector3& a)
{
	float l = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
	if (l > 0) {
		return Vector3(a.x / l, a.y / l, a.z / l);
	}
	return a;
}

float dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

float crossZ(const Vector3& a, const Vector3& b)
{
	return a.x * b.y - a.y * b.x;
}

float crossY(const Vector3& a, const Vector3& b)
{
	return a.x * b.z - a.z * b.x;
}


// ２次元ベクトルの一般関数-------------------------------------------------------
Vector2::Vector2(float x, float y)
	: x(x), y(y)
{
}

void Vector2::set(float x, float y)
{
	this->x = x; this->y = y;
}

Vector2 Vector2::operator+(const Vector2& v) const
{
	// ２次元ベクトルの加算
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator+(const float f) const
{
	// ２次元ベクトルとスカラーの加算
	return Vector2(x + f, y + f);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	// ２次元ベクトルの減算
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator-(const float f) const
{
	// ２次元ベクトルとスカラーの減算
	return Vector2(x - f, y - f);
}

Vector2 Vector2::operator*(const Vector2& v) const
{
	// ２次元ベクトルの乗算
	return Vector2(x * v.x, y * v.y);
}

Vector2 Vector2::operator*(float f) const
{
	// ２次元ベクトルとスカラーの乗算
	return Vector2(x * f, y * f);
}

Vector2 Vector2::operator/(const Vector2& v) const
{
	// ２次元ベクトルの除算
	return Vector2(x / v.x, y / v.y);
}

Vector2 Vector2::operator/(float f) const
{
	// ２次元ベクトルとスカラーの除算
	return Vector2(x / f, y / f);
}

Vector2 Vector2::operator-() const
{
	// ２次元ベクトルの符号反転
	return Vector2(-x, -y);
}

bool Vector2::operator==(const Vector2& v) const
{
	// 誤差を許容する
	return fabs(x - v.x) < EPSILON && fabs(y - v.y) < EPSILON;
}

bool Vector2::operator!=(const Vector2& v) const
{
	// 誤差を許容する
	return fabs(x - v.x) >= EPSILON || fabs(y - v.y) >= EPSILON;
}

void Vector2::operator=(const Vector2& v)
{
	// ２次元ベクトルの代入
	this->x = v.x; this->y = v.y;
}

void Vector2::operator=(const float f)
{
	// ２次元ベクトルの代入
	this->x = f; this->y = f;
}

void Vector2::operator+=(const Vector2& v)
{
	// ２次元ベクトルの加算代入
	x += v.x; y += v.y;
}

void Vector2::operator+=(const float f)
{
	// ２次元ベクトルとスカラーの加算代入
	x += f; y += f;
}

void Vector2::operator-=(const Vector2& v)
{
	// ２次元ベクトルの減算代入
	x -= v.x; y -= v.y;
}

void Vector2::operator-=(const float f)
{
	// ２次元ベクトルとスカラーの減算代入
	x -= f; y -= f;
}

void Vector2::operator*=(float f)
{
	// ２次元ベクトルとスカラーの乗算代入
	x *= f; y *= f;
}

void Vector2::operator*=(const Vector2& v)
{
	// ２次元ベクトルの乗算代入
	x *= v.x; y *= v.y;
}

void Vector2::operator/=(float f)
{
	// ２次元ベクトルとスカラーの除算代入
	x /= f; y /= f;
}

void Vector2::operator/=(const Vector2& v)
{
	// ２次元ベクトルの除算代入
	x /= v.x; y /= v.y;
}

DirectX::XMFLOAT2 Vector2::toXMFLOAT2() const
{
	return DirectX::XMFLOAT2(x, y);
}

DirectX::XMVECTOR Vector2::toXMVECTOR() const
{
	return DirectX::XMVectorSet(x, y, 0.0f, 0.0f);
}

float Vector2::sqMag() const
{
	// ２次元ベクトルの長さの２乗
	return x * x + y * y;
}

float Vector2::magSq() const
{
	// ２次元ベクトルの長さの２乗
	return x * x + y * y;
}

float Vector2::mag() const
{
	// ２次元ベクトルの長さ
	return sqrtf(x * x + y * y);
}

Vector2 Vector2::setMag(float mag)
{
	// ２次元ベクトルの長さを設定
	float len = sqrtf(x * x + y * y);
	if (len > 0) {
		mag /= len;
		x *= mag;
		y *= mag;
	}
	return Vector2(x, y);
}

Vector2 Vector2::limmit(float maxMag)
{
	// ２次元ベクトルの長さを制限
	float len = sqrtf(x * x + y * y);
	if (len > maxMag) {
		maxMag /= len;
		x *= maxMag;
		y *= maxMag;
	}
	return Vector2(x, y);
}

Vector2 Vector2::normalize()
{
	// ２次元ベクトルの正規化
	float len = sqrtf(x * x + y * y);
	if (len > 0) {
		x /= len;
		y /= len;
	}
	return Vector2(x, y);
}

Vector2 Vector2::lerp(const Vector2& v, float t) const
{
	// ２次元ベクトルの線形補間
	return Vector2(
		x + (v.x - x) * t,
		y + (v.y - y) * t
	);
}

float Vector2::dot(const Vector2& v) const
{
	// ２次元ベクトルの内積
	return x * v.x + y * v.y;
}

float Vector2::cross(const Vector2& v) const
{
	// ２次元ベクトルの外積
	return x * v.y - y * v.x;
}

float Vector2::crossY(const Vector2& v) const
{
	// ２次元ベクトルの外積
	return x * v.y - y * v.x;
}

Vector2 Vector2::zero()
{
	// ゼロベクトル
	return Vector2();
}

Vector2 Vector2::one()
{
	// １ベクトル
	return Vector2(1.0f, 1.0f);
}

Vector2 Vector2::right()
{
	// 右ベクトル
	return Vector2(1.0f, 0.0f);
}

Vector2 Vector2::up()
{
	// 上ベクトル
	return Vector2(0.0f, 1.0f);
}

Vector2 Vector2::left()
{
	// 左ベクトル
	return Vector2(-1.0f, 0.0f);
}

Vector2 Vector2::down()
{
	// 下ベクトル
	return Vector2(0.0f, -1.0f);
}


// ４次元ベクトルの一般関数-------------------------------------------------------
Vector4::Vector4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}

void Vector4::set(float x, float y, float z, float w)
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}

Vector4 Vector4::operator+(const Vector4& v) const
{
	// ４次元ベクトルの加算
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector4 Vector4::operator+(const float f) const
{
	// ４次元ベクトルとスカラーの加算
	return Vector4(x + f, y + f, z + f, w + f);
}

Vector4 Vector4::operator-(const Vector4& v) const
{
	// ４次元ベクトルの減算
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4 Vector4::operator-(const float f) const
{
	// ４次元ベクトルとスカラーの減算
	return Vector4(x - f, y - f, z - f, w - f);
}

Vector4 Vector4::operator*(const Vector4& v) const
{
	// ４次元ベクトルの乗算
	return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
}

Vector4 Vector4::operator*(float f) const
{
	// ４次元ベクトルとスカラーの乗算
	return Vector4(x * f, y * f, z * f, w * f);
}

Vector4 Vector4::operator/(const Vector4& v) const
{
	// ４次元ベクトルの除算
	return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
}

Vector4 Vector4::operator/(float f) const
{
	// ４次元ベクトルとスカラーの除算
	return Vector4(x / f, y / f, z / f, w / f);
}

Vector4 Vector4::operator-() const
{
	// ４次元ベクトルの符号反転
	return Vector4(-x, -y, -z, -w);
}

bool Vector4::operator==(const Vector4& v) const
{
	// 誤差を許容する
	return fabs(x - v.x) < EPSILON && fabs(y - v.y) < EPSILON && fabs(z - v.z) < EPSILON && fabs(w - v.w) < EPSILON;
}

bool Vector4::operator!=(const Vector4& v) const
{
	// 誤差を許容する
	return fabs(x - v.x) >= EPSILON || fabs(y - v.y) >= EPSILON || fabs(z - v.z) >= EPSILON || fabs(w - v.w) >= EPSILON;
}

void Vector4::operator=(const Vector4& v)
{
	// ４次元ベクトルの代入
	this->x = v.x; this->y = v.y; this->z = v.z; this->w = v.w;
}

void Vector4::operator=(const float f)
{
	// ４次元ベクトルの代入
	this->x = f; this->y = f; this->z = f; this->w = f;
}

void Vector4::operator+=(const Vector4& v)
{
	// ４次元ベクトルの加算代入
	x += v.x; y += v.y; z += v.z; w += v.w;
}

void Vector4::operator+=(const float f)
{
	// ４次元ベクトルとスカラーの加算代入
	x += f; y += f; z += f; w += f;
}

void Vector4::operator-=(const Vector4& v)
{
	// ４次元ベクトルの減算代入
	x -= v.x; y -= v.y; z -= v.z; w -= v.w;
}

void Vector4::operator-=(const float f)
{
	// ４次元ベクトルとスカラーの減算代入
	x -= f; y -= f; z -= f; w -= f;
}

void Vector4::operator*=(float f)
{
	// ４次元ベクトルとスカラーの乗算代入
	x *= f; y *= f; z *= f; w *= f;
}

void Vector4::operator*=(const Vector4& v)
{
	// ４次元ベクトルの乗算代入
	x *= v.x; y *= v.y; z *= v.z; w *= v.w;
}

void Vector4::operator/=(float f)
{
	// ４次元ベクトルとスカラーの除算代入
	x /= f; y /= f; z /= f; w /= f;
}

void Vector4::operator/=(const Vector4& v)
{
	// ４次元ベクトルの除算代入
	x /= v.x; y /= v.y; z /= v.z; w /= v.w;
}

DirectX::XMFLOAT4 Vector4::toXMFLOAT4() const
{
	return DirectX::XMFLOAT4(x, y, z, w);
}

DirectX::XMVECTOR Vector4::toXMVECTOR() const
{
	return DirectX::XMVectorSet(x, y, z, w);
}

float Vector4::sqMag() const
{
	// ４次元ベクトルの長さの２乗
	return x * x + y * y + z * z + w * w;
}

float Vector4::magSq() const
{
	// ４次元ベクトルの長さの２乗
	return x * x + y * y + z * z + w * w;
}

float Vector4::mag() const
{
	// ４次元ベクトルの長さ
	return sqrtf(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::setMag(float mag)
{
	// ４次元ベクトルの長さを設定
	float len = sqrtf(x * x + y * y + z * z + w * w);
	if (len > 0) {
		mag /= len;
		x *= mag;
		y *= mag;
		z *= mag;
		w *= mag;
	}
	return Vector4(x, y, z, w);
}

Vector4 Vector4::limmit(float maxMag)
{
	// ４次元ベクトルの長さを制限
	float len = sqrtf(x * x + y * y + z * z + w * w);
	if (len > maxMag) {
		maxMag /= len;
		x *= maxMag;
		y *= maxMag;
		z *= maxMag;
		w *= maxMag;
	}
	return Vector4(x, y, z, w);
}

Vector4 Vector4::normalize()
{
	// ４次元ベクトルの正規化
	float len = sqrtf(x * x + y * y + z * z + w * w);
	if (len > 0) {
		x /= len;
		y /= len;
		z /= len;
		w /= len;
	}
	return Vector4(x, y, z, w);
}

Vector4 Vector4::lerp(const Vector4& v, float t) const
{
	// ４次元ベクトルの線形補間
	return Vector4(
		x + (v.x - x) * t,
		y + (v.y - y) * t,
		z + (v.z - z) * t,
		w + (v.w - w) * t
	);
}

float Vector4::dot(const Vector4& v) const
{
	// ４次元ベクトルの内積
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vector4 Vector4::cross(const Vector4& v) const
{
	// ４次元ベクトルの外積
	return Vector4(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x,
		0.0f
	);
}

float Vector4::crossZ(const Vector4& v) const
{
	// ４次元ベクトルの外積
	return x * v.y - y * v.x;
}

float Vector4::crossY(const Vector4& v) const
{
	// ４次元ベクトルの外積
	return x * v.z - z * v.x;
}

float Vector4::crossX(const Vector4& v) const
{
	// ４次元ベクトルの外積
	return y * v.z - z * v.y;
}

Vector4 Vector4::zero()
{
	// ゼロベクトル
	return Vector4();
}

Vector4 Vector4::one()
{
	// １ベクトル
	return Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

Vector4 operator*(float f, const Vector4& v)
{
	// ４次元ベクトルとスカラーの乗算
	return Vector4(f * v.x, f * v.y, f * v.z, f * v.w);
}

Vector4 normalize(const Vector4& a)
{
	// ４次元ベクトルの正規化
	float l = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
	if (l > 0) {
		return Vector4(a.x / l, a.y / l, a.z / l, a.w / l);
	}
	return a;
}

float dot(const Vector4& a, const Vector4& b)
{
	// ４次元ベクトルの内積
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vector4 cross(const Vector4& a, const Vector4& b)
{
	// ４次元ベクトルの外積
	return Vector4(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		0.0f
	);
}

float crossZ(const Vector4& a, const Vector4& b)
{
	// ４次元ベクトルの外積
	return a.x * b.y - a.y * b.x;
}

float crossY(const Vector4& a, const Vector4& b)
{
	// ４次元ベクトルの外積
	return a.x * b.z - a.z * b.x;
}

float crossX(const Vector4& a, const Vector4& b)
{
	// ４次元ベクトルの外積
	return a.y * b.z - a.z * b.y;
}
