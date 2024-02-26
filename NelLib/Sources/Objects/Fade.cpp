#include "Fade.h"
#include <Managers/TextureManager.h>

Fade::Fade()
	: m_fFadeTime(0.0f)
	, m_fFadeTimeCount(0.0f)
	, m_FadeState(FADE_NONE)
{
	SetOrder(500);
	m_pSprite = AddComponent<SpriteComponent>();
	m_pSprite->SetTexture(TEXTURE_MANAGER.GetTexture(TextureManager::TEX_DEFAULT2));
	m_pTransform->SetScale(NORMAL_TEX_VEC);
}

Fade::~Fade()
{
}

void Fade::Init()
{
}

void Fade::Uninit()
{
}

void Fade::Update()
{
	if (m_FadeState == FADE_NONE) { return; }

	m_fFadeTimeCount += 1.0f / 60.0f;
	if (m_fFadeTimeCount >= m_fFadeTime)
	{
		m_fFadeTimeCount = m_fFadeTime;
		m_FadeState = FADE_NONE;
	}

	float alpha = 0.0f;
	if (m_FadeState == FADE_IN)
	{
		alpha = 1.0f - (m_fFadeTimeCount / m_fFadeTime);
	}
	else if (m_FadeState == FADE_OUT)
	{
		alpha = m_fFadeTimeCount / m_fFadeTime;
	}

	m_pSprite->SetAlpha(alpha);
}

void Fade::Draw()
{
}

void Fade::FadeIn(float time)
{
	// フェード中は処理を行わない
	if (m_FadeState != FADE_NONE) { return; }
	m_FadeState = FADE_IN;
	m_fFadeTime = time;
	m_fFadeTimeCount = 0.0f;
	m_pSprite->SetAlpha(1.0f);
}

void Fade::FadeOut(float time)
{
	// フェード中は処理を行わない
	if (m_FadeState != FADE_NONE) { return; }
	m_FadeState = FADE_OUT;
	m_fFadeTime = time;
	m_fFadeTimeCount = 0.0f;
	m_pSprite->SetAlpha(0.0f);
}
