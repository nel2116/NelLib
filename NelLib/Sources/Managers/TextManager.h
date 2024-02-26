#pragma once
// ====== インクルード部 ======
#include <string>
#include <vector>
#include <System/Singleton.h>
#include <System/VECTOR.h>
#include <System/DirectWriteCustomFont.h>

// ====== クラス宣言 ======
class TextManager : public Singleton<TextManager>
{
public:
	struct Text
	{
		std::string string;
		Vector2 pos;
	};

public:
	// デストラクタ
	~TextManager() { Uninit(); }

	// 初期化
	void Init();

	// 終了
	void Uninit();

	// 更新
	void Update();

	// 描画
	void Draw();

	// テキストの追加
	void AddText(std::string string, Vector2 pos);

private:
	// テキストのリスト
	std::vector<Text> m_TextList;

	DirectWriteCustomFont* m_pWrite;
	FontData m_FontData;
	int drawNum;

private: //	シングルトン関連
	friend class Singleton<TextManager>;
	TextManager() : drawNum(0), m_pWrite(nullptr), m_FontData() {}
};
// インスタンス取得
#define TEXT_MANAGER TextManager::GetInstance()