#pragma once

// ====== インクルード部 ======
#include <Objects/Camera/CameraBase.h>

// ====== 前方宣言 ======

// ====== クラス宣言 ======
class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug();

	void Update() override;

	void Uninit() override {}

private:
	// ====== メンバ変数 ======
	float m_radXZ;
	float m_radY;
	float m_distance;

};