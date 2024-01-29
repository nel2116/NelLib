#include "NelLib.h"
#include <DirectX/Renderer.h>
#include "GameObjects/testObject.h"

TestObject* g_pTestObject = nullptr;

void Init()
{
	// ===== ���������� =====
	window("Nel Game", 960, 540);

	// ===== �Q�[���I�u�W�F�N�g�̏����� =====
	g_pTestObject = new TestObject();
	g_pTestObject->Init();
}

void Input()
{
	// ===== ���͏��� =====
	UpdateInput();
}

void Update()
{
	// ===== �Q�[���I�u�W�F�N�g�̍X�V =====
	g_pTestObject->Update();
}

void Draw()
{
	RENDERER.Begin();

#if _DEBUG
	DrawGrid();		// �O���b�h���̕`��
#endif // _DEBUG

	// ===== �Q�[���I�u�W�F�N�g�̕`�� =====
	g_pTestObject->Draw();

	RENDERER.End();
}
void Uninit()
{
	// ===== �Q�[���I�u�W�F�N�g�̏I������ =====
	g_pTestObject->Uninit();

	// ===== �I������ =====
	SAFE_DELETE(g_pTestObject);
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