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
	TransformComponent(Object* owner);

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
	Vector3 GetPosition() { return m_position; }
	Vector3 GetOldPosition() { return m_oldPosition; }
	DirectX::XMFLOAT3 GetPosition3() { return DirectX::XMFLOAT3(m_position.x, m_position.y, m_position.z); }
	DirectX::XMFLOAT3 GetOldPosition3() { return DirectX::XMFLOAT3(m_oldPosition.x, m_oldPosition.y, m_oldPosition.z); }

	// 位置の設定
	void SetPosition(Vector3 position) { m_oldPosition = m_position; m_position = position; }
	void SetPosition(float x, float y, float z) { m_oldPosition = m_position; m_position = Vector3(x, y, z); }
	void SetPosition(DirectX::XMFLOAT3 position) { m_oldPosition = m_position; m_position = Vector3(position.x, position.y, position.z); }

	// 回転の取得
	QUATERNION GetRotation() { return m_rotation; }
	QUATERNION GetOldRotation() { return m_oldRotation; }

	// 回転の設定
	void SetRotation(QUATERNION rotation) { m_oldRotation = m_rotation; m_rotation = rotation; }
	void SetRotation(float x, float y, float z, float w) { m_oldRotation = m_rotation; m_rotation = QUATERNION(x, y, z, w); }

	// スケールの取得
	Vector3 GetScale() { return m_scale; }
	Vector3 GetOldScale() { return m_oldScale; }

	// スケールの設定
	void SetScale(Vector3 scale) { m_oldScale = m_scale; m_scale = scale; }
	void SetScale(float x, float y, float z) { m_oldScale = m_scale; m_scale = Vector3(x, y, z); }

	// ローカル行列の取得
	DirectX::XMFLOAT4X4 GetLocalMatrix();
	// ワールド行列の取得
	DirectX::XMFLOAT4X4 GetWorldMatrix();

	// 移動する関数
	void translate(Vector3 move);
	void translate(float x, float y, float z);

	// 回転する関数
	void rotate(QUATERNION rotate);
	void rotate(float x, float y, float z);

	// 拡大する関数
	void scale(Vector3 scale);
	void scale(float x, float y, float z);

private:
	// 位置
	Vector3 m_position;
	Vector3 m_oldPosition;
	// 回転
	QUATERNION m_rotation;
	QUATERNION m_oldRotation;
	// スケール
	Vector3 m_scale;
	Vector3 m_oldScale;

	// ローカル行列
	DirectX::XMFLOAT4X4 m_localMatrix;

	// ワールド行列
	DirectX::XMFLOAT4X4 m_worldMatrix;
};