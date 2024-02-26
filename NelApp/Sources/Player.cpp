#include "Player.h"
#include <System/Input.h>
#include <Objects/Camera/CameraPlayer.h>
#include <Managers/ModelManager.h>

Player::Player()
	: m_fSpeed(0.2f)
	, m_fRotSpeed(1.0f)
{
	m_pModel = MODEL_MANAGER.GetModel(ModelManager::MODEL_PLAYER);
	m_pVS = NEW VertexShader();
	m_pVS->Load("../NelLib/Assets/Shaders/VS_Model.cso");
	m_pModel->SetVertexShader(m_pVS);

	GetTransform()->SetScale(Vector3() + 0.1f);
	GetTransform()->SetPosition(Vector3(0.0f, -2.5f, 0.0f));
}

Player::~Player()
{
	SAFE_DELETE(m_pVS);
}

void Player::Init()
{
}

void Player::Uninit()
{
}

void Player::Update()
{
	Move();
}

void Player::Draw()
{
	if (!m_pCamera) return;
	if (!m_pModel) return;
	DirectX::XMFLOAT4X4 mat[3];
	mat[0] = GetTransform()->GetWorldMatrix();
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	m_pVS->WriteBuffer(0, mat);
	m_pModel->Draw();
}

void Player::Move()
{
	if (!m_pCamera) return;

	bool bMove = false;

	Vector3 pos = GetTransform()->GetPosition();
	DirectX::XMFLOAT3 camPos = m_pCamera->GetTransform()->GetPosition3();
	DirectX::XMFLOAT3 camLook = m_pCamera->GetLook().toXMFLOAT3();

	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&camPos);
	DirectX::XMVECTOR vCamLook = DirectX::XMLoadFloat3(&camLook);

	DirectX::XMVECTOR vFront;	// カメラの正面方向のベクトル
	vFront = DirectX::XMVectorSubtract(vCamLook, vCamPos);
	vFront = DirectX::XMVector3Normalize(vFront);

	// カメラの右方向のベクトル
	DirectX::XMMATRIX matRotSide = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f));
	DirectX::XMVECTOR vSide = DirectX::XMVector3TransformCoord(vFront, matRotSide);
	DirectX::XMVECTOR vMove = DirectX::XMVectorZero();

	if (IsKeyPress('W')) { bMove = true; vMove = DirectX::XMVectorAdd(vMove, vFront); }
	if (IsKeyPress('S')) { bMove = true; vMove = DirectX::XMVectorSubtract(vMove, vFront); }
	if (IsKeyPress('D')) { bMove = true; vMove = DirectX::XMVectorAdd(vMove, vSide); }
	if (IsKeyPress('A')) { bMove = true; vMove = DirectX::XMVectorSubtract(vMove, vSide); }

	if (IsKeyPress(VK_SPACE)) { bMove = true; pos.y += m_fSpeed; }
	if (IsKeyPress(VK_SHIFT)) { bMove = true; pos.y -= m_fSpeed; }

	vMove = DirectX::XMVectorMultiply(vMove, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	vMove = DirectX::XMVector3Normalize(vMove);
	vMove = DirectX::XMVectorScale(vMove, m_fSpeed);

	// カメラの正面方向にモデルを向ける
	// 現在向いている方向
	QUATERNION pRot = GetTransform()->GetRotation();
	QUATERNION Forward;
	float angle = static_cast<CameraPlayer*>(m_pCamera)->GetRadXZ();
	// ラジアンから角度に変換
	angle = RAD2DEG(angle) + 180.0f;
	Forward = Forward.AngleAxis(angle, Vector3::up());

	// 回転の補間
//	pRot = pRot.lerp(Forward, 1.0f);
	// 回転の設定
	GetTransform()->SetRotation(Forward);

	// 座標の更新
	DirectX::XMFLOAT3 move;
	DirectX::XMStoreFloat3(&move, vMove);
	pos.x += move.x; pos.y += move.y; pos.z += move.z;
	GetTransform()->SetPosition(pos);
}
