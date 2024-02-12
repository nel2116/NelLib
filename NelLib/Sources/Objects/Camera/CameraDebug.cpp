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
	// �J�����̈ʒu�𓮂���
	if (IsKeyPress(VK_UP)) { m_radY += MOVE_SPEED; }
	if (IsKeyPress(VK_DOWN)) { m_radY -= MOVE_SPEED; }
	if (IsKeyPress(VK_LEFT)) { m_radXZ -= MOVE_SPEED; }
	if (IsKeyPress(VK_RIGHT)) { m_radXZ += MOVE_SPEED; }
	if (IsKeyPress(VK_SHIFT)) { m_distance += MOVE_SPEED; }
	if (IsKeyPress(VK_CONTROL)) { m_distance -= MOVE_SPEED; }

	// �J�����̒����_�𓮂���
	if (IsKeyPress('W')) { m_look.z += MOVE_SPEED; }
	if (IsKeyPress('S')) { m_look.z -= MOVE_SPEED; }
	if (IsKeyPress('A')) { m_look.x -= MOVE_SPEED; }
	if (IsKeyPress('D')) { m_look.x += MOVE_SPEED; }
	if (IsKeyPress('Q')) { m_look.y -= MOVE_SPEED; }
	if (IsKeyPress('E')) { m_look.y += MOVE_SPEED; }

	// �J�������㉺�ɉ�]���Ȃ��悤�ɐ���
	if (m_radY > M_PI / 2.0f) { m_radY = M_PI / 2.0f; }
	if (m_radY < -M_PI / 2.0f) { m_radY = -M_PI / 2.0f; }

	// �J�����̒��~�_�ƈʒu�������ɂȂ�Ȃ��悤�ɐ���
	if (m_distance < 0.1f) { m_distance = 0.1f; }

	// �J�����̈ʒu���v�Z
	m_pos.x = cosf(m_radY) * sinf(m_radXZ) * m_distance + m_look.x;
	m_pos.y = sinf(m_radY) * m_distance + m_look.y;
	m_pos.z = cosf(m_radY) * cosf(m_radXZ) * m_distance + m_look.z;

}




