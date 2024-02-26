#include "TitleUI.h"
#include <Managers/TextureManager.h>

TitleUI::TitleUI()
	: Object()
	, m_pSprite(nullptr)
{
	m_pSprite = AddComponent<SpriteComponent>();
	m_pTransform->SetScale(NORMAL_TEX_VEC);
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	m_pSprite->SetTexture(TEXTURE_MANAGER.GetTexture(TextureManager::TEX_TEST));
}

void TitleUI::Uninit()
{
}

void TitleUI::Update()
{
}

void TitleUI::Draw()
{
}
