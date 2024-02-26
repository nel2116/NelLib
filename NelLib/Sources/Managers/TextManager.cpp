#include "TextManager.h"
#include <DirectX/Renderer.h>
#include <System/Input.h>

void TextManager::Init()
{
	// DirectWriteCustomFontのインスタンスを生成
	m_pWrite = NEW DirectWriteCustomFont(&m_FontData);
	// 初期化
	m_pWrite->Init(RENDERER.GetSwapChain());

	// 日本語ロケールのフォント名を取得
	m_pWrite->GetFontFamilyName(m_pWrite->fontCollection.Get(), L"ja-JP");

	// フォントデータの設定
	m_FontData.fontSize = 30;
	m_FontData.fontWeight = DWRITE_FONT_WEIGHT_ULTRA_BLACK;
	m_FontData.Color = D2D1::ColorF(D2D1::ColorF::White);
	m_FontData.font = m_pWrite->GetFontName(0);
	m_FontData.shadowColor = D2D1::ColorF(D2D1::ColorF::White);
	m_FontData.shadowOffset = D2D1::Point2F(1.0f, -1.0f);

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
	// 描画フレームが0になったら削除
	for (auto it = m_TextList.begin(); it != m_TextList.end();)
	{
		it->drawFrame--;
		if (it->drawFrame <= 0)
		{
			it = m_TextList.erase(it);
		}
		else
		{
			it++;
		}
	}
	if (IsKeyPress('U')) { m_pos.y += 1.1f; }
	if (IsKeyPress('J')) { m_pos.y -= 1.1f; }
	if (IsKeyPress('H')) { m_pos.x -= 1.1f; }
	if (IsKeyPress('K')) { m_pos.x += 1.1f; }

}

void TextManager::Draw()
{
	for (auto text : m_TextList)
	{
		if (text.string == "HP")
		{
			m_pWrite->DrawString(text.string, m_pos, D2D1_DRAW_TEXT_OPTIONS_NONE);
		}
		else
		{
			m_pWrite->DrawString(text.string, text.pos, D2D1_DRAW_TEXT_OPTIONS_NONE);
		}
	}
}

void TextManager::AddText(std::string string, Vector2 pos, int frame)
{
	Text text;
	text.string = string;
	text.pos = pos;
	text.drawFrame = frame;
	m_TextList.push_back(text);
}
