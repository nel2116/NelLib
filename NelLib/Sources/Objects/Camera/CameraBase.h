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
	DirectX::XMFLOAT4X4 GetTransposedViewMatrix() const;

	// 転置済みプロジェクション行列を取得
	DirectX::XMFLOAT4X4 GetTransposedProjectionMatrix() const;

protected:
	DirectX::XMFLOAT3 m_pos, m_look, m_up;	// ビュー行列に必要な変数
	float m_fov, m_aspect, m_near, m_far;	// プロジェクション行列に必要な変数
};

