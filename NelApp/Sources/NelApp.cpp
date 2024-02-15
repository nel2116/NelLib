#include "NelLib.h"
#include <DirectX/Renderer.h>
#include <Managers/ObjectsManager.h>
#include <Managers/CameraManager.h>
#include "GameObjects/testObject.h"
#include "GameObjects/UI_testObject.h"

void Init()
{
	// ===== ���������� =====
	window("Nel Game", 960, 540);
	OBJECTS_MANAGER.AddObject<TestObject>();
//	UI_TestObject* UI = OBJECTS_MANAGER.AddObject<UI_TestObject>();
	//UI->SetOrder(100);
}

void Input()
{
}

void Update()
{
	// ===== �X�V���� =====
	OBJECTS_MANAGER.Update();
}

void Draw()
{
	// ===== �`�揈�� =====
	CameraBase* camera = CAMERA_MANAGER.GetNowCamera();
	Geometory::SetView(camera->GetTransposedViewMatrix());
	Geometory::SetProjection(camera->GetTransposedProjectionMatrix());

#if _DEBUG	// �f�o�b�O���̂�
	DrawGrid();		// �O���b�h���̕`��
#endif // _DEBUG

	OBJECTS_MANAGER.Draw();
}

void Uninit()
{
}