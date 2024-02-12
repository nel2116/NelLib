#include "NelLib.h"
#include <DirectX/Renderer.h>
#include <Managers/ObjectsManager.h>
#include "GameObjects/testObject.h"
#include <Objects/Camera/CameraDebug.h>

TestObject* g_pTestObject = nullptr;

void Init()
{
	// ===== ���������� =====
	window("Nel Game", 960, 540);
	TestObject* test = OBJECTS_MANAGER.AddObject<TestObject>();
	CameraDebug* camera = OBJECTS_MANAGER.AddObject<CameraDebug>();
	test->SetCamera(camera);

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
	CameraDebug* camera = OBJECTS_MANAGER.GetObject<CameraDebug>();
	Geometory::SetView(camera->GetTransposedViewMatrix());
	Geometory::SetProjection(camera->GetTransposedProjectionMatrix());
#if _DEBUG
	DrawGrid();		// �O���b�h���̕`��
#endif // _DEBUG

	OBJECTS_MANAGER.Draw();
}

void Uninit()
{
}