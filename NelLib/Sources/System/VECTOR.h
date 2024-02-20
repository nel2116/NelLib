#pragma once
#include <DirectXMath.h>

// �x�N�g��2�^
class Vector2 {
public:
	// �����o�ϐ�
	// 2�����x�N�g���̐���
	union
	{
		// 2�����x�N�g���̐���
		float i[2];
		struct // ���W
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

	// ���Z�q
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

	// ���
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

	// ��r
	float sqMag() const;
	float magSq() const;//�@�\��sqMag�Ɠ���
	float mag() const;
	Vector2 setMag(float mag);
	Vector2 limmit(float maxMag);
	Vector2 normalize();
	// ���
	Vector2 lerp(const Vector2& v, float t) const;
	float dot(const Vector2& v)const;
	float cross(const Vector2& v)const;
	float crossY(const Vector2& v)const;//�O��Y�����̂݌v�Z(�Q�c�p)

	// ���̑�
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

// �x�N�g��3�^
class Vector3 {
public:
	// �����o�ϐ�
	// 3�����x�N�g���̐���
	union
	{
		// 3�����x�N�g���̐���
		float v[3];
		struct // ���W
		{
			float x;
			float y;
			float z;
		};
	};

	// �R���X�g���N�^
	Vector3(float x = 0, float y = 0, float z = 0);
	void set(float x, float y, float z = 0);	// �l��ݒ肷��
	// ���Z�q
	Vector3 operator+(const Vector3& v) const;	// �x�N�g���Ƀx�N�g���𑫂�
	Vector3 operator+(const float f) const;		// �x�N�g���ɃX�J���[�𑫂�
	Vector3 operator-(const Vector3& v) const;	// �x�N�g������x�N�g��������
	Vector3 operator-(const float f) const;		// �x�N�g������X�J���[������
	Vector3 operator*(const Vector3& v) const;	// �x�N�g���Ƀx�N�g����������
	Vector3 operator*(float f) const;			// �x�N�g���ɃX�J���[��������
	Vector3 operator/(const Vector3& v) const;	// �x�N�g�����x�N�g���Ŋ���
	Vector3 operator/(float f) const;			// �x�N�g�����X�J���[�Ŋ���
	Vector3 operator-() const;					// �x�N�g���𔽓]����
	bool operator==(const Vector3& v) const;	// �x�N�g������������
	bool operator!=(const Vector3& v) const;	// �x�N�g�����������Ȃ���

	// ���
	void operator=(const Vector3& v);			// �x�N�g����������
	void operator=(const float f);				// �X�J���[��������
	void operator+=(const Vector3& v);			// �x�N�g���Ƀx�N�g���𑫂�
	void operator+=(const float f);				// �x�N�g���ɃX�J���[�𑫂�
	void operator-=(const Vector3& v);			// �x�N�g������x�N�g��������
	void operator-=(const float f);				// �x�N�g������X�J���[������
	void operator*=(float f);					// �x�N�g���ɃX�J���[��������
	void operator*=(const Vector3& v);			// �x�N�g���Ƀx�N�g����������
	void operator/=(float f);					// �x�N�g�����X�J���[�Ŋ���
	void operator/=(const Vector3& v);			// �x�N�g�����x�N�g���Ŋ���

	// �ϊ�
	DirectX::XMFLOAT3 toXMFLOAT3() const;
	DirectX::XMVECTOR toXMVECTOR() const;

	// ��r
	float sqMag() const;
	float magSq() const;//�@�\��sqMag�Ɠ���
	float mag() const;
	Vector3 setMag(float mag);		// �x�N�g���̑傫����ݒ肷��
	Vector3 limmit(float maxMag);	// �x�N�g���̑傫���𐧌�����
	Vector3 normalize();
	// ���
	Vector3 lerp(const Vector3& v, float t) const;
	float dot(const Vector3& v)const;
	Vector3 cross(const Vector3& v)const;
	float crossZ(const Vector3& v)const;//�O��Z�����̂݌v�Z(�Q�c�p)
	float crossY(const Vector3& v)const;//�O��Y�����̂݌v�Z(�Q�c�p)

	// ���̑�
	// zero()�̓[���x�N�g����Ԃ�
	static Vector3 zero();
	// one()�͑S������1�̃x�N�g����Ԃ�
	static Vector3 one();
	// right()��x������1�̃x�N�g����Ԃ�
	static Vector3 right();
	// up()��y������1�̃x�N�g����Ԃ�
	static Vector3 up();
	// forward()��z������1�̃x�N�g����Ԃ�
	static Vector3 forward();
	// left()��x������-1�̃x�N�g����Ԃ�
	static Vector3 left();
	// down()��y������-1�̃x�N�g����Ԃ�
	static Vector3 down();
	// back()��z������-1�̃x�N�g����Ԃ�
	static Vector3 back();
};


Vector3 operator* (float f, const Vector3& v);// VECTOR = float * VECTOR
Vector3 normalize(const Vector3& a);
float dot(const Vector3& a, const Vector3& b);
Vector3 cross(const Vector3& a, const Vector3& b);
float crossZ(const Vector3& a, const Vector3& b);
float crossY(const Vector3& a, const Vector3& b);

// �x�N�g��4�^
class Vector4 {
public:
	// �����o�ϐ�
	// 4�����x�N�g���̐���
	union
	{
		// 4�����x�N�g���̐���
		float v[4];
		struct // ���W
		{
			float x;
			float y;
			float z;
			float w;
		};
		struct // �F
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

	// �R���X�g���N�^
	Vector4(float x = 0, float y = 0, float z = 0, float w = 1.0f);
	void set(float x, float y, float z = 0, float w = 0);	// �l��ݒ肷��
	// ���Z�q
	Vector4 operator+(const Vector4& v) const;	// �x�N�g���Ƀx�N�g���𑫂�
	Vector4 operator+(const float f) const;		// �x�N�g���ɃX�J���[�𑫂�
	Vector4 operator-(const Vector4& v) const;	// �x�N�g������x�N�g��������
	Vector4 operator-(const float f) const;		// �x�N�g������X�J���[������
	Vector4 operator*(const Vector4& v) const;	// �x�N�g���Ƀx�N�g����������
	Vector4 operator*(float f) const;			// �x�N�g���ɃX�J���[��������
	Vector4 operator/(const Vector4& v) const;	// �x�N�g�����x�N�g���Ŋ���
	Vector4 operator/(float f) const;			// �x�N�g�����X�J���[�Ŋ���
	Vector4 operator-() const;					// �x�N�g���𔽓]����
	bool operator==(const Vector4& v) const;	// �x�N�g������������
	bool operator!=(const Vector4& v) const;	// �x�N�g�����������Ȃ���

	// ���
	void operator=(const Vector4& v);			// �x�N�g����������
	void operator=(const float f);				// �X�J���[��������
	void operator+=(const Vector4& v);			// �x�N�g���Ƀx�N�g���𑫂�
	void operator+=(const float f);				// �x�N�g���ɃX�J���[�𑫂�
	void operator-=(const Vector4& v);			// �x�N�g������x�N�g��������
	void operator-=(const float f);				// �x�N�g������X�J���[������
	void operator*=(float f);					// �x�N�g���ɃX�J���[��������
	void operator*=(const Vector4& v);			// �x�N�g���Ƀx�N�g����������
	void operator/=(float f);					// �x�N�g�����X�J���[�Ŋ���
	void operator/=(const Vector4& v);			// �x�N�g�����x�N�g���Ŋ���

	// �ϊ�
	DirectX::XMFLOAT4 toXMFLOAT4() const;
	DirectX::XMVECTOR toXMVECTOR() const;

	// ��r
	float sqMag() const;
	float magSq() const;//�@�\��sqMag�Ɠ���
	float mag() const;
	Vector4 setMag(float mag);
	Vector4 limmit(float maxMag);
	Vector4 normalize();
	// ���
	Vector4 lerp(const Vector4& v, float t) const;
	float dot(const Vector4& v)const;
	Vector4 cross(const Vector4& v)const;
	float crossZ(const Vector4& v)const;//�O��Z�����̂݌v�Z(�Q�c�p)
	float crossY(const Vector4& v)const;//�O��Y�����̂݌v�Z(�Q�c�p)
	float crossX(const Vector4& v)const;//�O��X�����̂݌v�Z(�Q�c�p)

	// ���̑�
	// zero()�̓[���x�N�g����Ԃ�
	static Vector4 zero();
	// one()�͑S������1�̃x�N�g����Ԃ�
	static Vector4 one();
};

Vector4 operator* (float f, const Vector4& v);// VECTOR = float * VECTOR
Vector4 normalize(const Vector4& a);
float dot(const Vector4& a, const Vector4& b);
Vector4 cross(const Vector4& a, const Vector4& b);
float crossZ(const Vector4& a, const Vector4& b);
float crossY(const Vector4& a, const Vector4& b);
float crossX(const Vector4& a, const Vector4& b);



