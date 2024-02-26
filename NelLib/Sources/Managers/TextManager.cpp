#include "TextManager.h"
#include <DirectX/Renderer.h>

void TextManager::Init()
{
	// DirectWriteCustomFontのインスタンスを生成
	m_pWrite = NEW DirectWriteCustomFont(&m_FontData);
	// 初期化
	m_pWrite->Init(RENDERER.GetSwapChain());

	// 日本語ロケールのフォント名を取得
	m_pWrite->GetFontFamilyName(m_pWrite->fontCollection.Get(), L"ja-JP");

	// フォントデータの設定
	m_FontData.fontSize = 60;
	m_FontData.fontWeight = DWRITE_FONT_WEIGHT_ULTRA_BLACK;
	m_FontData.Color = D2D1::ColorF(D2D1::ColorF::White);
	m_FontData.font = m_pWrite->GetFontName(0);
	m_FontData.shadowColor = D2D1::ColorF(D2D1::ColorF::White);
	m_FontData.shadowOffset = D2D1::Point2F(5.0f, -5.0f);

	// フォントをセット
	m_pWrite->SetFont(m_FontData);
}

void TextManager::Uninit()
{
	// フォントの解放
	SAFE_DELETE(m_pWrite);
}

void TextManager::Update()
{
}

void TextManager::AddText(std::string string, Vector2 pos)
{
	Text text;
	text.string = string;
	text.pos = pos;
	m_TextList.push_back(text);
}

void TextManager::Draw()
{
	for (auto text : m_TextList)
	{
		m_pWrite->DrawString(text.string, text.pos, D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
	m_TextList.clear();
}
