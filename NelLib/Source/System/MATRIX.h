#pragma once
#include "VECTOR.h"

class MATRIX {
public:
    float   _11, _12, _13, _14,
        _21, _22, _23, _24,
        _31, _32, _33, _34,
        _41, _42, _43, _44;
    //行列をつくる
    /// <summary>
    /// 単位行列を作成
    /// </summary>
    void identity();
    /// <summary>
    /// 平行移動行列を作成
    /// </summary>
    /// <param name="x">X軸方向の移動量</param>
    /// <param name="y">Y軸方向の移動量</param>
    /// <param name="z">Z軸方向の移動量</param>
    void translate(float x, float y, float z = 0);
    /// <summary>
    /// 平行移動行列を作成
    /// </summary>
    /// <param name="t">移動量</param>
    void translate(class VECTOR& t);
    /// <summary>
    /// 拡大縮小行列を作成
    /// </summary>
    /// <param name="x">X軸方向の拡大率</param>
    /// <param name="y">Y軸方向の拡大率</param>
    /// <param name="z">Z軸方向の拡大率</param>
    void scaling(float x, float y, float z = 1);
    /// <summary>
    /// Y軸の回転行列を作成
    /// </summary>
    /// <param name="angle">回転角度</param>
    void rotateY(float angle);
    /// <summary>
    /// X軸の回転行列を作成
    /// </summary>
    /// <param name="angle">回転角度</param>
    void rotateX(float angle);
    /// <summary>
    /// Z軸の回転行列を作成
    /// </summary>
    /// <param name="angle">回転角度</param>
    void rotateZ(float angle);
    /// <summary>
    /// X軸、Y軸、Z軸の回転行列を作成
    /// </summary>
    /// <param name="r">回転角度</param>
    void rotateYXZ(const VECTOR& r);
    /// <summary>
    /// クォータニオンから回転行列を作成
    /// </summary>
    /// <param name="q">クォータニオン</param>
    void rotateQuaternion(const class QUATERNION& q);
    //ビュー、プロジェクションをつくる
    /// <summary>
    /// カメラのビュー行列を作成
    /// </summary>
    /// <param name="camPos">カメラの位置</param>
    /// <param name="lookatPos">注視点</param>
    /// <param name="upVec">上方向のベクトル</param>
    void camera(const VECTOR& camPos, const VECTOR& lookatPos, const VECTOR& upVec);
    /// <summary>
    /// 透視投影行列を作成
    /// </summary>
    /// <param name="angle">視野角</param>
    /// <param name="aspect">アスペクト比</param>
    /// <param name="n">ニアクリップ</param>
    /// <param name="f">ファークリップ</param>
    void pers(float angle, float aspect, float n, float f);
    /// <summary>
    /// 正射影行列を作成
    /// </summary>
    /// <param name="l">左端</param>
    /// <param name="r">右端</param>
    /// <param name="b">下端</param>
    /// <param name="t">上端</param>
    /// <param name="n">ニアクリップ</param>
    /// <param name="f">ファークリップ</param>
    void ortho(float l, float r, float b, float t, float n, float f);
    //行列同士の掛け算
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
    //行列と行列の掛け算
    MATRIX operator*(const MATRIX& m) const;
    //行列とベクトルの掛け算
    VECTOR operator*(const VECTOR& v) const;
};
MATRIX createMatFromQtn(const class QUATERNION& q);