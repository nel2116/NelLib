#include "Slime.h"
#include <Managers/ObjectsManager.h>
#include <Player.h>
#include <Managers/TextureManager.h>

void Slime::Init()
{
	m_pPlayer = OBJECTS_MANAGER.GetObjects<Player>();
	// ステータスを初期化
	m_pStatus->SetName("スライム");
	m_pStatus->SetLevel(1);
	m_pStatus->SetHp(100);
	m_pStatus->SetMaxHp(100);
	m_pStatus->SetMp(0);
	m_pStatus->SetMaxMp(0);
	m_pStatus->SetAttack(10);
	m_pStatus->SetDefence(5);
	m_pStatus->SetSpeed(5);
	m_pStatus->SetXp(0);
	m_pStatus->SetMaxXp(100);
	m_pStatus->SetGold(0);
	m_pStatus->SetMagicResistance(0);
	m_pStatus->SetPhysicalResistance(0);
	m_Sprite->SetTexture(TEXTURE_MANAGER.GetTexture(TextureManager::TEX_SLIME));
}

void Slime::Uninit()
{
}

void Slime::Draw()
{
}

void Slime::Attack()
{
}

void Slime::Defence()
{
}

void Slime::Skill()
{
}
