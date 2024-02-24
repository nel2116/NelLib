#pragma once
// ====== �C���N���[�h ======
#include <System/Scenes/Scene.h>
#include "Field.h"
#include "Player.h"

// ====== �N���X�̐錾 ======
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene() {}

	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

private:
	Field* m_Field;
	Player* m_Player;
};