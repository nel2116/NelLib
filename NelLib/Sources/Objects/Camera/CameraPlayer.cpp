#include "CameraPlayer.h"
#include <Managers/ObjectsManager.h>
#include <Player.h>
#include <System/Input.h>

CameraPlayer::CameraPlayer()
	: m_radXZ(0.0f)
	, m_radY(1.0f)
	, m_distance(5.0f)
{
}

void CameraPlayer::Update()
{
	Player* player = OBJECTS_MANAGER.GetObjects<Player>();
	if (!player) { return; }
	m_look = player->GetTransform()->GetPosition();

	// ‰ñ“]
	const float rotSpeed = 0.1f;
	if (IsKeyPress(VK_UP)) { m_radY += rotSpeed; }
	if (IsKeyPress(VK_DOWN)) { m_radY -= rotSpeed; }
	if (IsKeyPress(VK_LEFT)) { m_radXZ += rotSpeed; }
	if (IsKeyPress(VK_RIGHT)) { m_radXZ -= rotSpeed; }

	// ƒJƒƒ‰‚ªã‰º‚É‰ñ“]‚µ‚È‚¢‚æ‚¤‚É§ŒÀ
	if (m_radY > M_PI / 2.0f - 0.1f) { m_radY = M_PI / 2.0f - 0.1f; }
	if (m_radY < -M_PI / 2.0f + 0.1f) { m_radY = -M_PI / 2.0f + 0.1f; }

	Vector3 pos = GetTransform()->GetPosition();
	pos.x = cosf(m_radY) * sinf(m_radXZ) * m_distance + m_look.x;
	pos.y = sinf(m_radY) * m_distance + m_look.y;
	pos.z = cosf(m_radY) * cosf(m_radXZ) * m_distance + m_look.z;
	GetTransform()->SetPosition(pos);
}

