#pragma once
#include <Objects/Object.h>
#include <DirectXMath.h>

class CameraBase : public Object
{
public:
	CameraBase();
	~CameraBase() {}

	virtual void Update() override {}

	virtual void Uninit() override {}

	// 転置済みビュー行列を取得
	virtual DirectX::XMFLOAT4X4 GetViewMatrix();

	// 転置済みプロジェクション行列を取得
	virtual DirectX::XMFLOAT4X4 GetProjectionMatrix();

protected:
	// ビュー行列を更新
	virtual void UpdateViewMatrix();
	// プロジェクション行列を更新
	virtual void UpdateProjectionMatrix();

	DirectX::XMFLOAT3 m_look, m_up;	// ビュー行列に必要な変数
	float m_fov, m_aspect, m_near, m_far;	// プロジェクション行列に必要な変数
	DirectX::XMFLOAT4X4 m_view, m_projection;	// ビュー行列、プロジェクション行列
};

