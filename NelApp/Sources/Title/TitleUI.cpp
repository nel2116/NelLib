#include "TitleUI.h"
#include <Managers/TextureManager.h>

TitleUI::TitleUI()
	: Object()
	, m_pSprite(nullptr)
{
	m_pSprite = AddComponent<SpriteComponent>();
	//	m_pTransform->SetScale(NORMAL_TEX_VEC);
	m_pTransform->SetPosition(Vector3(1.9f, -1.0f, 0.0f));
	m_pTransform->SetScale(Vector3(1.55f, 0.65f, 1.0f));
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	m_pSprite->SetTexture(TEXTURE_MANAGER.GetTexture(TextureManager::TEX_TITLE_UI));
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
