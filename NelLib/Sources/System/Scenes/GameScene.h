#pragma once
// ====== �C���N���[�h ======
#include "Scene.h"

// ====== �N���X�̐錾 ======
class GameScene : public Scene
{
public:
	// ������
	void Init() override;

	// �I��
	void Uninit() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

private:

};