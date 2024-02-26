#include "TitleBackground.h"
#include <Managers/TextureManager.h>

TitleBackGround::TitleBackGround()
	: m_pSprite(nullptr)
{
	m_pSprite = AddComponent<SpriteComponent>();
	m_pTransform->SetScale(NORMAL_TEX_VEC);
	SetOrder(30);
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Init()
{
	m_pSprite->SetTexture(TEXTURE_MANAGER.GetTexture(TextureManager::TEX_TITLE));
}

void TitleBackGround::Uninit()
{
}

void TitleBackGround::Update()
{
}

void TitleBackGround::Draw()
{
}
