#include "../../NelLib/Source/NelLib.h"
#include "../../NelLib/Source/DirectX/Renderer.h"

void Init()
{
	window("Nel Game", 960, 540);
}
void Input()
{

}
void Update()
{

}
void Draw()
{
	RENDERER.Begin();

	RENDERER.End();

	RENDERER.Present();
}
void Uninit()
{
}

void gmain()
{
	Init();
	while (!quit())
	{
		if (escKeyPressed()) { closeWindow(); }
		// �ȉ��ɃQ�[���̏���������
		// ===== ���͏��� =====
		Input();
		// ===== �X�V���� =====
		Update();
		// ===== �`�揈�� =====
		Draw();
	}
	Uninit();
}