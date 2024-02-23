#include "NelLib.h"
#include <DirectX/Renderer.h>
#include <Managers/ObjectsManager.h>
#include <Managers/CameraManager.h>
#include <Managers/SceneManager.h>

void Init()
{
	// ===== ���������� =====
	window("Nel Game", 1280, 720);


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