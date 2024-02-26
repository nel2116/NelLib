#include "BattleUI.h"
#include <Managers/TextManager.h>
#include <Managers/TextureManager.h>

BattleUI::BattleUI()
	: m_pSprite(nullptr)
{
	m_pSprite = AddComponent<SpriteComponent>();
	m_pSprite->SetTexture(TEXTURE_MANAGER.GetTexture(TextureManager::TEX_BATTLE_UI));
	m_pTransform->SetScale(NORMAL_TEX_VEC);
	SetOrder(60);
}

BattleUI::~BattleUI()
{
}

void BattleUI::Init()
{
}

void BattleUI::Uninit()
{
}

void BattleUI::Update()
{
}

void BattleUI::Draw()
{
}
