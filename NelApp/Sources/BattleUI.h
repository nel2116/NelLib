#pragma once
// ====== インクルード部 ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>

// ====== クラスの定義 ======
class BattleUI : public Object
{
public:
	BattleUI();
	~BattleUI();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	SpriteComponent* m_pSprite;
};