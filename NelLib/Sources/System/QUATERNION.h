#pragma once
#include <cmath>
#include <DirectXMath.h>
#include"mathUtil.h"
#include"VECTOR.h"

#define PI 3.1415926f

class QUATERNION
{
public:
	// メンバ変数
	float w; // 実数部
	float x; // 虚数部のx成分
	float y; // 虚数部のy成分
	float z; // 虚数部のz成分

	// コンストラクタ
	QUATERNION(); // デフォルトコンストラクタ
	QUATERNION(float x, float y, float z, float w); // 引数付きコンストラクタ
	QUATERNION(const QUATERNION& q); // コピーコンストラクタ


	// デストラクタ
	~QUATERNION();

	// 代入演算子
	QUATERNION& operator=(const QUATERNION& q);
	QUATERNION& operator=(const DirectX::XMVECTOR& v);

	// 単項演算子
	QUATERNION operator-() const; // 符号反転
	QUATERNION operator~() const; // 共役

	// 二項演算子
	QUATERNION operator+(const QUATERNION& q) const; // 加算
	QUATERNION operator+(float s) const; // スカラー加算
	QUATERNION operator-(const QUATERNION& q) const; // 減算
	QUATERNION operator-(float s) const; // スカラー減算
	QUATERNION operator*(const QUATERNION& q) const; // 乗算
	QUATERNION operator*(float s) const; // スカラー乗算
	QUATERNION operator/(const QUATERNION& q) const; // 除算
	QUATERNION operator/(float s) const; // スカラー除算

	// 代入演算子
	QUATERNION& operator+=(const QUATERNION& q); // 加算
	QUATERNION& operator+=(float s); // スカラー加算
	QUATERNION& operator-=(const QUATERNION& q); // 減算
	QUATERNION& operator-=(float s); // スカラー減算
	QUATERNION& operator*=(const QUATERNION& q); // 乗算
	QUATERNION& operator*=(float s); // スカラー乗算
	QUATERNION& operator/=(const QUATERNION& q); // 除算
	QUATERNION& operator/=(float s); // スカラー除算

	// その他の演算子	
	QUATERNION operator*(const Vector3& v) const; // 乗算
	QUATERNION operator/(const Vector3& v) const; // 除算

	// メンバ関数
	float magnitude() const; // ノルム（大きさ）を返す
	QUATERNION normalize() const; // 正規化したクォータニオンを返す
	QUATERNION inverse() const; // 逆元のクォータニオンを返す
	float dot(const QUATERNION& q) const; // 内積を返す
	QUATERNION cross(const QUATERNION& q) const; // 外積を返す
	QUATERNION slerp(const QUATERNION& q, float t) const; // 球面線形補間を返す
	QUATERNION lerp(const QUATERNION& q, float t) const; // 線形補間を返す
	DirectX::XMVECTOR toXMVECTOR() const; // クォータニオンをXMVECTORに変換して返す
	DirectX::XMMATRIX toMatrix() const; // クォータニオンを行列に変換して返す
	DirectX::XMMATRIX toMatrixTranspose() const; // クォータニオンを行列に変換して返す
	DirectX::XMMATRIX toMatrixInverse() const; // クォータニオンを行列に変換して返す
	DirectX::XMFLOAT4 toFloat4() const; // クォータニオンをXMFLOAT4に変換して返す
	DirectX::XMFLOAT4X4 toFloat4x4() const; // クォータニオンをXMFLOAT4X4に変換して返す

	// クォータニオンの生成
	QUATERNION AngleAxis(float angle, Vector3 axis) const;// 軸回りの回転を表すクォータニオンを生成して返す

	// 静的メンバ関数
	// クォータニオンの生成
	static QUATERNION createIdentity(); // 単位クォータニオンを生成して返す
};
