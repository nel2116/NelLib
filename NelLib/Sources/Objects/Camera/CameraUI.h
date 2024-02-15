#pragma once

#include "CameraBase.h"

// ====== クラスの宣言 ======
class CameraUI : public CameraBase
{

public:
	// コンストラクタ
	CameraUI();
	// デストラクタ
	~CameraUI() {}

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;
protected:
	// ビュー行列を更新
	void UpdateViewMatrix() override;

	// プロジェクション行列を更新
	void UpdateProjectionMatrix() override;

private:
	float m_ViewLeft, m_ViewRight, m_ViewTop, m_ViewBottom;
};