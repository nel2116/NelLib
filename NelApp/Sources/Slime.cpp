#include "Slime.h"
#include <Managers/ObjectsManager.h>
#include <Managers/TextureManager.h>
#include <Managers/TextManager.h>
#include <Player.h>

void Slime::Init()
{
	m_pPlayer = OBJECTS_MANAGER.GetObjects<Player>();
	// �X�e�[�^�X��������
	m_pStatus->SetName("�X���C��");
	m_pStatus->SetLevel(1);
	m_pStatus->SetHp(100);
	m_pStatus->SetMaxHp(100);
	m_pStatus->SetMp(0);
	m_pStatus->SetMaxMp(0);
	m_pStatus->SetAttack(3);
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

void Slime::Attack()
{
	m_pPlayer->Damage(m_pStatus->GetAttack());
	TEXT_MANAGER.AddText(m_pStatus->GetName() + "���v���C���[��" + std::to_string(m_pStatus->GetAttack()) + "�_���[�W�^�����I", Vector2(530.0f, 530.0f), 60);
}

void Slime::Defence()
{
	TEXT_MANAGER.AddText(m_pStatus->GetName() + "�͎����ł߂��I", Vector2(530.0f, 530.0f), 60);
}

void Slime::Skill()
{
	TEXT_MANAGER.AddText(m_pStatus->GetName() + "�̓v���v���k���Ă���I", Vector2(530.0f, 530.0f), 60);
}
