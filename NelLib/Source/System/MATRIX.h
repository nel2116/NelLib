#pragma once
#include "VECTOR.h"

class MATRIX {
public:
    float   _11, _12, _13, _14,
        _21, _22, _23, _24,
        _31, _32, _33, _34,
        _41, _42, _43, _44;
    //�s�������
    /// <summary>
    /// �P�ʍs����쐬
    /// </summary>
    void identity();
    /// <summary>
    /// ���s�ړ��s����쐬
    /// </summary>
    /// <param name="x">X�������̈ړ���</param>
    /// <param name="y">Y�������̈ړ���</param>
    /// <param name="z">Z�������̈ړ���</param>
    void translate(float x, float y, float z = 0);
    /// <summary>
    /// ���s�ړ��s����쐬
    /// </summary>
    /// <param name="t">�ړ���</param>
    void translate(class VECTOR& t);
    /// <summary>
    /// �g��k���s����쐬
    /// </summary>
    /// <param name="x">X�������̊g�嗦</param>
    /// <param name="y">Y�������̊g�嗦</param>
    /// <param name="z">Z�������̊g�嗦</param>
    void scaling(float x, float y, float z = 1);
    /// <summary>
    /// Y���̉�]�s����쐬
    /// </summary>
    /// <param name="angle">��]�p�x</param>
    void rotateY(float angle);
    /// <summary>
    /// X���̉�]�s����쐬
    /// </summary>
    /// <param name="angle">��]�p�x</param>
    void rotateX(float angle);
    /// <summary>
    /// Z���̉�]�s����쐬
    /// </summary>
    /// <param name="angle">��]�p�x</param>
    void rotateZ(float angle);
    /// <summary>
    /// X���AY���AZ���̉�]�s����쐬
    /// </summary>
    /// <param name="r">��]�p�x</param>
    void rotateYXZ(const VECTOR& r);
    /// <summary>
    /// �N�H�[�^�j�I�������]�s����쐬
    /// </summary>
    /// <param name="q">�N�H�[�^�j�I��</param>
    void rotateQuaternion(const class QUATERNION& q);
    //�r���[�A�v���W�F�N�V����������
    /// <summary>
    /// �J�����̃r���[�s����쐬
    /// </summary>
    /// <param name="camPos">�J�����̈ʒu</param>
    /// <param name="lookatPos">�����_</param>
    /// <param name="upVec">������̃x�N�g��</param>
    void camera(const VECTOR& camPos, const VECTOR& lookatPos, const VECTOR& upVec);
    /// <summary>
    /// �������e�s����쐬
    /// </summary>
    /// <param name="angle">����p</param>
    /// <param name="aspect">�A�X�y�N�g��</param>
    /// <param name="n">�j�A�N���b�v</param>
    /// <param name="f">�t�@�[�N���b�v</param>
    void pers(float angle, float aspect, float n, float f);
    /// <summary>
    /// ���ˉe�s����쐬
    /// </summary>
    /// <param name="l">���[</param>
    /// <param name="r">�E�[</param>
    /// <param name="b">���[</param>
    /// <param name="t">��[</param>
    /// <param name="n">�j�A�N���b�v</param>
    /// <param name="f">�t�@�[�N���b�v</param>
    void ortho(float l, float r, float b, float t, float n, float f);
    //�s�񓯎m�̊|���Z
    void mul(const MATRIX& m);
    void mulTranslate(float x, float y, float z = 0);
    void mulTranslate(const VECTOR& t);
    void mulScaling(float x, float y, float z = 1);
    void mulScaling(const VECTOR& s);
    void mulRotateZ(float angle);
    void mulRotateY(float angle);
    void mulRotateX(float angle);
    void mulRotateYXZ(const VECTOR& r);
    void mulRotateQuaternion(const class QUATERNION& q);
    //�s��ƍs��̊|���Z
    MATRIX operator*(const MATRIX& m) const;
    //�s��ƃx�N�g���̊|���Z
    VECTOR operator*(const VECTOR& v) const;
};
MATRIX createMatFromQtn(const class QUATERNION& q);