#include "Player.h"
#include <System/Input.h>
#include <Objects/Camera/CameraBase.h>

Player::Player()
	: m_fSpeed(0.1f)
	, m_fRotSpeed(0.1f)
{
	m_pModel = NEW Model();
	m_pModel->Load("Assets/Models/eyeBat/eyebat.fbx");
	m_pVS = NEW VertexShader();
	m_pVS->Load("../NelLib/Assets/Shaders/VS_Model.cso");
	m_pModel->SetVertexShader(m_pVS);

	GetTransform()->SetScale(Vector3() + 0.1f);
	GetTransform()->SetPosition(Vector3(0.0f, -0.5f, 0.0f));
}

Player::~Player()
{
	SAFE_DELETE(m_pModel);
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

	vMove = DirectX::XMVectorMultiply(vMove, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	vMove = DirectX::XMVector3Normalize(vMove);
	vMove = DirectX::XMVectorScale(vMove, m_fSpeed);

	// 座標の更新
	DirectX::XMFLOAT3 move;
	DirectX::XMStoreFloat3(&move, vMove);
	Vector3 pos = GetTransform()->GetPosition();
	pos.x += move.x; pos.y += move.y; pos.z += move.z;
	GetTransform()->SetPosition(pos);
}
