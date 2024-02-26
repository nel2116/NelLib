#pragma once
// ====== �C���N���[�h�� ======
#include <Objects/Object.h>
#include <Components/SpriteComponent.h>

// ====== �N���X�̒�` ======
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