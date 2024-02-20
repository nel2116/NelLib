#include "NelLib.h"
#include <DirectX/Renderer.h>
#include <Managers/ObjectsManager.h>
#include <Managers/CameraManager.h>
#include "GameObjects/testObject.h"
#include <Components/SpriteComponent.h>

void Init()
{
	// ===== ���������� =====
	window("Nel Game", 960, 540);
	OBJECTS_MANAGER.AddObject<TestObject>();
	TestObject* UI = OBJECTS_MANAGER.AddObject<TestObject>();
	UI->AddComponent<SpriteComponent>();
	UI->SetOrder(100);
	UI->GetComponent<TransformComponent>()->SetPosition(Vector3(1.0f, 0.0f, 0.0f));

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
	Geometory::SetView(camera->GetViewMatrix());
	Geometory::SetProjection(camera->GetProjectionMatrix());

#if _DEBUG	// �f�o�b�O���̂�
	DrawGrid();		// �O���b�h���̕`��
#endif // _DEBUG

	OBJECTS_MANAGER.Draw();
}

void Uninit()
{
}