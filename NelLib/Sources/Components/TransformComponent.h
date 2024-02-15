#pragma once

// ====== インクルード ======
#include <Components/Component.h>
#include <DirectXMath.h>
#include <System/VECTOR.h>
#include <System/QUATERNION.h>

// ====== クラスの宣言 ======
class TransformComponent : public Component
{
public:
	// コンストラクタ
	TransformComponent(Object* owner)
		: Component(owner)
		, m_position(VECTOR(0.0f, 0.0f, 0.0f))
		, m_rotation(QUATERNION(0.0f, 0.0f, 0.0f, 1.0f))
		, m_scale(VECTOR(1.0f, 1.0f, 1.0f))
		, m_localMatrix(DirectX::XMFLOAT4X4())
		, m_worldMatrix(DirectX::XMFLOAT4X4()) {}

	// デストラクタ
	~TransformComponent() {}

	// 初期化
	void Init() override;
	// 終了
	void Uninit() override;
	// 更新
	void Update() override;

	// ゲッター、セッター
	// 位置の取得
	VECTOR GetPosition() { return m_position; }
	DirectX::XMFLOAT3 GetPosition3() { return DirectX::XMFLOAT3(m_position.x, m_position.y, m_position.z); }

	// 位置の設定
	void SetPosition(VECTOR position) { m_position = position; }
	void SetPosition(float x, float y, float z) { m_position = VECTOR(x, y, z); }
	void SetPosition(DirectX::XMFLOAT3 position) { m_position = VECTOR(position.x, position.y, position.z); }
	// 回転の取得
	QUATERNION GetRotation() { return m_rotation; }
	// 回転の設定
	void SetRotation(QUATERNION rotation) { m_rotation = rotation; }
	void SetRotation(float x, float y, float z, float w) { m_rotation = QUATERNION(x, y, z, w); }
	// スケールの取得
	VECTOR GetScale() { return m_scale; }
	// スケールの設定
	void SetScale(VECTOR scale) { m_scale = scale; }
	void SetScale(float x, float y, float z) { m_scale = VECTOR(x, y, z); }

	// ローカル行列の取得
	DirectX::XMFLOAT4X4 GetLocalMatrix();
	// ワールド行列の取得
	DirectX::XMFLOAT4X4 GetWorldMatrix();

	// 移動する関数
	void translate(VECTOR move);
	void translate(float x, float y, float z);

	// 回転する関数
	void rotate(QUATERNION rotate);
	void rotate(float x, float y, float z);

	// 拡大する関数
	void scale(VECTOR scale);
	void scale(float x, float y, float z);

private:
	// 位置
	VECTOR m_position;
	// 回転
	QUATERNION m_rotation;
	// スケール
	VECTOR m_scale;

	// ローカル行列
	DirectX::XMFLOAT4X4 m_localMatrix;

	// ワールド行列
	DirectX::XMFLOAT4X4 m_worldMatrix;
};