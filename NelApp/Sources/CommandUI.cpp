#include "CommandUI.h"
#include <Managers/TextureManager.h>
#include <Managers/TextManager.h>
#include <Managers/ObjectsManager.h>
#include <Managers/BattleManager.h>
#include <System/Input.h>
#include <Player.h>

CommandUI::CommandUI()
	: m_pSprite(nullptr)
	, m_nNowCmd(0)
	, m_nFrame(0)
	, m_bReturn(false)
{
	m_pSprite = AddComponent<SpriteComponent>();
	SetOrder(60);

}

CommandUI::~CommandUI()
{
	m_pSprite = nullptr;
}

void CommandUI::Init()
{
	// 画像の読み込み
	m_pSprite->SetTexture(TEXTURE_MANAGER.GetTexture(TextureManager::TEX_COMMAND_UI));
	m_pTransform->SetPosition(Vector3(-1.03f, -1.14f, 0.0f));
	m_pTransform->SetScale(Vector3(0.76f, 0.95f, 1.0f));
	m_pPlayer = OBJECTS_MANAGER.GetObjects<Player>();
}

void CommandUI::Uninit()
{
}

void CommandUI::Update()
{
	m_nFrame++;
	if (m_nFrame % 8 != 1) { return; }
	// プレイヤーのターンじゃない場合は処理しない
	if (BATTLE_MANAGER.GetBattleState() != BattleManager::BATTLE_STATE_PLAYER_TURN) { return; }

	// コマンドの選択
	int nCmd = m_nNowCmd;

	// ループするようにする
	if (IsKeyPress('S')) { nCmd++; }
	if (IsKeyPress('W')) { nCmd--; }
	if (IsKeyPress(VK_RETURN)) { m_bReturn = true; }
	if (nCmd >= 3)nCmd = 3;
	if (nCmd <= 0)nCmd = 0;
	m_nNowCmd = nCmd;
	if (m_bReturn) { m_pPlayer->Action(m_nNowCmd); }
}

void CommandUI::Draw()
{
	std::string str[CMD_MAX] =
	{
		"攻撃",
		"防御",
		"アイテム",
		"逃げる",
	};

	for (int i = 0; i < CMD_MAX; ++i)
	{
		if (m_nNowCmd == i) { str[i] = "> " + str[i]; }
		TEXT_MANAGER.AddText(str[i], Vector2(370.0f, 510.0f + (i * 40)), 1);
	}
}
