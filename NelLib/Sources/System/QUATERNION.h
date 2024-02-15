#pragma once
#include"mathUtil.h"
#include"VECTOR.h"
#include <DirectXMath.h>

class QUATERNION
{
public:
	// コンストラクタ
	QUATERNION() : m_x(0.0f), m_y(0.0f), m_z(0.0f), m_w(1.0f) {}
	// コンストラクタ
	QUATERNION(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}
	// コンストラクタ
	QUATERNION(DirectX::XMFLOAT4 quaternion) : m_x(quaternion.x), m_y(quaternion.y), m_z(quaternion.z), m_w(quaternion.w) {}
	// デストラクタ
	~QUATERNION() {}

	// ゲッター、セッター
	// クォータニオンの設定
	void SetQuaternion(DirectX::XMFLOAT4 quaternion) { m_x = quaternion.x; m_y = quaternion.y; m_z = quaternion.z; m_w = quaternion.w; }

	// クォータニオンの設定
	void SetQuaternion(float x, float y, float z, float w) { m_x = x; m_y = y; m_z = z; m_w = w; }

	// クォータニオンの設定
	void SetQuaternion(QUATERNION quaternion) { m_x = quaternion.GetX(); m_y = quaternion.GetY(); m_z = quaternion.GetZ(); m_w = quaternion.GetW(); }

	// クォータニオンの設定
	void SetQuaternion(VECTOR axis, float angle);

	// Xの取得
	float GetX() { return m_x; }
	// Xの設定
	void SetX(float x) { m_x = x; }
	// Yの取得
	float GetY() { return m_y; }
	// Yの設定
	void SetY(float y) { m_y = y; }
	// Zの取得
	float GetZ() { return m_z; }
	// Zの設定
	void SetZ(float z) { m_z = z; }
	// Wの取得
	float GetW() { return m_w; }
	// Wの設定
	void SetW(float w) { m_w = w; }

	// 回転行列の取得
	DirectX::XMFLOAT4X4 GetRotationMatrix() { return m_rotationMatrix; }

	// 回転する関数
	void rotate(QUATERNION rotate);

	// 回転する関数
	void rotate(VECTOR rotate);

	// 回転する関数
	void rotate(float x, float y, float z);

	// 回転する関数
	void rotate(VECTOR axis, float angle);

	// leap関数
	void lerp(QUATERNION start, QUATERNION end, float t);

	// slerp関数
	void slerp(QUATERNION start, QUATERNION end, float t);

	// クォータニオンの取得
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

	// 回転行列
	DirectX::XMFLOAT4X4 m_rotationMatrix;
};
