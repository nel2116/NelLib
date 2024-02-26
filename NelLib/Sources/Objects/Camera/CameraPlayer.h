#pragma once
// ====== インクルード部 ======
#include <Objects/Camera/CameraBase.h>

// ====== クラス宣言 ======
class CameraPlayer : public CameraBase
{
public:
	// コンストラクタ
	CameraPlayer();
	// デストラクタ
	~CameraPlayer() {}

	void Update() override;

	void Uninit() override {}

	float GetRadXZ() { return m_radXZ; }
	float GetRadY() { return m_radY; }

private:
	// ====== メンバ変数 ======
	float m_radXZ;
	float m_radY;
	float m_distance;
};