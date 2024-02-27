#pragma once
// ====== インクルード部 ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>

class Player;
// ====== クラスの定義 ======
class CommandUI : public Object
{
public:
	enum COMMAND_TYPE
	{
		CMD_ATTACK,
		CMD_DEFENCE,
		CMD_ITEM,
		CMD_ESCAPE,
		CMD_MAX,
	};
public:
	CommandUI();
	~CommandUI();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void FlagDown() { m_bReturn = false; }

private:
	int m_nNowCmd;	//
	int m_nFrame;
	bool m_bReturn;
	SpriteComponent* m_pSprite;
	Player* m_pPlayer;
};