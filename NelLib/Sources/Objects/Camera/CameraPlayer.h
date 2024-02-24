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

private:
	// ====== メンバ変数 ======
	float m_radXZ;
	float m_radY;
	float m_distance;
};