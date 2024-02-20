#pragma once
#include <DirectXMath.h>

// ベクトル2型
class Vector2 {
public:
	// メンバ変数
	// 2次元ベクトルの成分
	union
	{
		// 2次元ベクトルの成分
		float i[2];
		struct // 座標
		{
			float x;
			float y;
		};
		struct // UV
		{
			float u;
			float v;
		};
	};

	Vector2(float x = 0, float y = 0);
	void set(float x, float y);

	// 演算子
	Vector2 operator+(const Vector2& v) const;
	Vector2 operator+(const float f) const;
	Vector2 operator-(const Vector2& v) const;
	Vector2 operator-(const float f) const;
	Vector2 operator*(const Vector2& v) const;
	Vector2 operator*(float f) const;
	Vector2 operator/(const Vector2& v) const;
	Vector2 operator/(float f) const;
	Vector2 operator-() const;
	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;

	// 代入
	void operator=(const Vector2& v);
	void operator=(const float f);
	void operator+=(const Vector2& v);
	void operator+=(const float f);
	void operator-=(const Vector2& v);
	void operator-=(const float f);
	void operator*=(float f);
	void operator*=(const Vector2& v);
	void operator/=(float f);
	void operator/=(const Vector2& v);

	DirectX::XMFLOAT2 toXMFLOAT2() const;
	DirectX::XMVECTOR toXMVECTOR() const;

	// 比較
	float sqMag() const;
	float magSq() const;//機能はsqMagと同じ
	float mag() const;
	Vector2 setMag(float mag);
	Vector2 limmit(float maxMag);
	Vector2 normalize();
	// 補間
	Vector2 lerp(const Vector2& v, float t) const;
	float dot(const Vector2& v)const;
	float cross(const Vector2& v)const;
	float crossY(const Vector2& v)const;//外積Y成分のみ計算(２Ｄ用)

	// その他
	static Vector2 zero();
	static Vector2 one();
	static Vector2 right();
	static Vector2 up();
	static Vector2 left();
	static Vector2 down();
};
Vector2 operator* (float f, const Vector2& v);// VECTOR = float * VECTOR
Vector2 normalize(const Vector2& a);
float dot(const Vector2& a, const Vector2& b);
float cross(const Vector2& a, const Vector2& b);
float crossY(const Vector2& a, const Vector2& b);

// ベクトル3型
class Vector3 {
public:
	// メンバ変数
	// 3次元ベクトルの成分
	union
	{
		// 3次元ベクトルの成分
		float v[3];
		struct // 座標
		{
			float x;
			float y;
			float z;
		};
	};

	// コンストラクタ
	Vector3(float x = 0, float y = 0, float z = 0);
	void set(float x, float y, float z = 0);	// 値を設定する
	// 演算子
	Vector3 operator+(const Vector3& v) const;	// ベクトルにベクトルを足す
	Vector3 operator+(const float f) const;		// ベクトルにスカラーを足す
	Vector3 operator-(const Vector3& v) const;	// ベクトルからベクトルを引く
	Vector3 operator-(const float f) const;		// ベクトルからスカラーを引く
	Vector3 operator*(const Vector3& v) const;	// ベクトルにベクトルをかける
	Vector3 operator*(float f) const;			// ベクトルにスカラーをかける
	Vector3 operator/(const Vector3& v) const;	// ベクトルをベクトルで割る
	Vector3 operator/(float f) const;			// ベクトルをスカラーで割る
	Vector3 operator-() const;					// ベクトルを反転する
	bool operator==(const Vector3& v) const;	// ベクトルが等しいか
	bool operator!=(const Vector3& v) const;	// ベクトルが等しくないか

	// 代入
	void operator=(const Vector3& v);			// ベクトルを代入する
	void operator=(const float f);				// スカラーを代入する
	void operator+=(const Vector3& v);			// ベクトルにベクトルを足す
	void operator+=(const float f);				// ベクトルにスカラーを足す
	void operator-=(const Vector3& v);			// ベクトルからベクトルを引く
	void operator-=(const float f);				// ベクトルからスカラーを引く
	void operator*=(float f);					// ベクトルにスカラーをかける
	void operator*=(const Vector3& v);			// ベクトルにベクトルをかける
	void operator/=(float f);					// ベクトルをスカラーで割る
	void operator/=(const Vector3& v);			// ベクトルをベクトルで割る

	// 変換
	DirectX::XMFLOAT3 toXMFLOAT3() const;
	DirectX::XMVECTOR toXMVECTOR() const;

	// 比較
	float sqMag() const;
	float magSq() const;//機能はsqMagと同じ
	float mag() const;
	Vector3 setMag(float mag);		// ベクトルの大きさを設定する
	Vector3 limmit(float maxMag);	// ベクトルの大きさを制限する
	Vector3 normalize();
	// 補間
	Vector3 lerp(const Vector3& v, float t) const;
	float dot(const Vector3& v)const;
	Vector3 cross(const Vector3& v)const;
	float crossZ(const Vector3& v)const;//外積Z成分のみ計算(２Ｄ用)
	float crossY(const Vector3& v)const;//外積Y成分のみ計算(２Ｄ用)

	// その他
	// zero()はゼロベクトルを返す
	static Vector3 zero();
	// one()は全成分が1のベクトルを返す
	static Vector3 one();
	// right()はx成分が1のベクトルを返す
	static Vector3 right();
	// up()はy成分が1のベクトルを返す
	static Vector3 up();
	// forward()はz成分が1のベクトルを返す
	static Vector3 forward();
	// left()はx成分が-1のベクトルを返す
	static Vector3 left();
	// down()はy成分が-1のベクトルを返す
	static Vector3 down();
	// back()はz成分が-1のベクトルを返す
	static Vector3 back();
};


Vector3 operator* (float f, const Vector3& v);// VECTOR = float * VECTOR
Vector3 normalize(const Vector3& a);
float dot(const Vector3& a, const Vector3& b);
Vector3 cross(const Vector3& a, const Vector3& b);
float crossZ(const Vector3& a, const Vector3& b);
float crossY(const Vector3& a, const Vector3& b);

// ベクトル4型
class Vector4 {
public:
	// メンバ変数
	// 4次元ベクトルの成分
	union
	{
		// 4次元ベクトルの成分
		float v[4];
		struct // 座標
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct // 色
		{
			float r;
			float g;
			float b;
			float a;
		};
		struct // UV
		{
			float top;
			float bottom;
			float left;
			float right;
		};
	};

	// コンストラクタ
	Vector4(float x = 0, float y = 0, float z = 0, float w = 1.0f);
	void set(float x, float y, float z = 0, float w = 0);	// 値を設定する
	// 演算子
	Vector4 operator+(const Vector4& v) const;	// ベクトルにベクトルを足す
	Vector4 operator+(const float f) const;		// ベクトルにスカラーを足す
	Vector4 operator-(const Vector4& v) const;	// ベクトルからベクトルを引く
	Vector4 operator-(const float f) const;		// ベクトルからスカラーを引く
	Vector4 operator*(const Vector4& v) const;	// ベクトルにベクトルをかける
	Vector4 operator*(float f) const;			// ベクトルにスカラーをかける
	Vector4 operator/(const Vector4& v) const;	// ベクトルをベクトルで割る
	Vector4 operator/(float f) const;			// ベクトルをスカラーで割る
	Vector4 operator-() const;					// ベクトルを反転する
	bool operator==(const Vector4& v) const;	// ベクトルが等しいか
	bool operator!=(const Vector4& v) const;	// ベクトルが等しくないか

	// 代入
	void operator=(const Vector4& v);			// ベクトルを代入する
	void operator=(const float f);				// スカラーを代入する
	void operator+=(const Vector4& v);			// ベクトルにベクトルを足す
	void operator+=(const float f);				// ベクトルにスカラーを足す
	void operator-=(const Vector4& v);			// ベクトルからベクトルを引く
	void operator-=(const float f);				// ベクトルからスカラーを引く
	void operator*=(float f);					// ベクトルにスカラーをかける
	void operator*=(const Vector4& v);			// ベクトルにベクトルをかける
	void operator/=(float f);					// ベクトルをスカラーで割る
	void operator/=(const Vector4& v);			// ベクトルをベクトルで割る

	// 変換
	DirectX::XMFLOAT4 toXMFLOAT4() const;
	DirectX::XMVECTOR toXMVECTOR() const;

	// 比較
	float sqMag() const;
	float magSq() const;//機能はsqMagと同じ
	float mag() const;
	Vector4 setMag(float mag);
	Vector4 limmit(float maxMag);
	Vector4 normalize();
	// 補間
	Vector4 lerp(const Vector4& v, float t) const;
	float dot(const Vector4& v)const;
	Vector4 cross(const Vector4& v)const;
	float crossZ(const Vector4& v)const;//外積Z成分のみ計算(２Ｄ用)
	float crossY(const Vector4& v)const;//外積Y成分のみ計算(２Ｄ用)
	float crossX(const Vector4& v)const;//外積X成分のみ計算(２Ｄ用)

	// その他
	// zero()はゼロベクトルを返す
	static Vector4 zero();
	// one()は全成分が1のベクトルを返す
	static Vector4 one();
};

Vector4 operator* (float f, const Vector4& v);// VECTOR = float * VECTOR
Vector4 normalize(const Vector4& a);
float dot(const Vector4& a, const Vector4& b);
Vector4 cross(const Vector4& a, const Vector4& b);
float crossZ(const Vector4& a, const Vector4& b);
float crossY(const Vector4& a, const Vector4& b);
float crossX(const Vector4& a, const Vector4& b);



