#include "CameraDebug.h"
#include <System/Input.h>
#include <System/mathUtil.h>

#define MOVE_SPEED 0.1f

CameraDebug::CameraDebug()
	: m_radXZ(0.0f)
	, m_radY(0.0f)
	, m_distance(5.0f)
{
}

CameraDebug::~CameraDebug()
{
}

void CameraDebug::Update()
{
	DirectX::XMFLOAT3 pos = m_pTransform->GetPosition3();
	// �J�����̈ʒu�𓮂���
	if (IsKeyPress(VK_UP)) { m_radY += MOVE_SPEED; }
	if (IsKeyPress(VK_DOWN)) { m_radY -= MOVE_SPEED; }
	if (IsKeyPress(VK_LEFT)) { m_radXZ += MOVE_SPEED; }
	if (IsKeyPress(VK_RIGHT)) { m_radXZ -= MOVE_SPEED; }
	if (IsKeyPress(VK_SHIFT)) { m_distance += MOVE_SPEED; }
	if (IsKeyPress(VK_CONTROL)) { m_distance -= MOVE_SPEED; }

	// �J�����̒����_�������Ă�x�N�g�ɍ��킹�ē�����
	// �J�����̈ʒu�ƒ����_�̃x�N�g��
	DirectX::XMVECTOR vCamPos = DirectX::XMLoadFloat3(&pos);
	DirectX::XMVECTOR vCamLook = DirectX::XMLoadFloat3(&m_look);

	// �J�����̐��ʕ����̃x�N�g��
	DirectX::XMVECTOR vFront;
	vFront = DirectX::XMVectorSubtract(vCamLook, vCamPos);
	vFront = DirectX::XMVector3Normalize(vFront);

	// �J�����̉E�����̃x�N�g��
	DirectX::XMMATRIX matRotSide = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(90.0f));
	DirectX::XMVECTOR vSide = DirectX::XMVector3TransformCoord(vFront, matRotSide);
	DirectX::XMVECTOR vMove = DirectX::XMVectorZero();

	// �J�����̈ʒu�𓮂���
	if (IsKeyPress('W')) { vMove = DirectX::XMVectorAdd(vMove, vFront); }
	if (IsKeyPress('S')) { vMove = DirectX::XMVectorSubtract(vMove, vFront); }
	if (IsKeyPress('A')) { vMove = DirectX::XMVectorSubtract(vMove, vSide); }
	if (IsKeyPress('D')) { vMove = DirectX::XMVectorAdd(vMove, vSide); }
	if (IsKeyPress('Q')) { m_look.y += 0.1f; }
	if (IsKeyPress('E')) { m_look.y -= 0.1f; }

	// �J�����̈ʒu���v�Z
	// �v�}��
	vMove = DirectX::XMVectorMultiply(vMove, DirectX::XMVectorSet(1.0f, 0.0f, 1.0f, 0.0f));
	vMove = DirectX::XMVector3Normalize(vMove);
	vMove = DirectX::XMVectorScale(vMove, 0.1f);

	DirectX::XMFLOAT3 move;
	DirectX::XMStoreFloat3(&move, vMove);
	m_look.x += move.x;
	m_look.y += move.y;
	m_look.z += move.z;

	// �J�������㉺�ɉ�]���Ȃ��悤�ɐ���
	if (m_radY > M_PI / 2.0f - 0.1f) { m_radY = M_PI / 2.0f - 0.1f; }
	if (m_radY < -M_PI / 2.0f + 0.1f) { m_radY = -M_PI / 2.0f + 0.1f; }

	// �J�����̒��~�_�ƈʒu�������ɂȂ�Ȃ��悤�ɐ���
	if (m_distance < 0.1f) { m_distance = 0.1f; }

	// �J�����̈ʒu���v�Z
	pos.x = cosf(m_radY) * sinf(m_radXZ) * m_distance + m_look.x;
	pos.y = sinf(m_radY) * m_distance + m_look.y;
	pos.z = cosf(m_radY) * cosf(m_radXZ) * m_distance + m_look.z;
	m_pTransform->SetPosition(pos);
}




