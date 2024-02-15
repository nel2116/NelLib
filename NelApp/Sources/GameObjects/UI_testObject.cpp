#include "UI_testObject.h"
#include <Managers/TextureManager.h>
#include <Managers/CameraManager.h>

void UI_TestObject::Init()
{
	//	m_pCamera = CAMERA_MANAGER.GetCamera(CameraManager::E_CAM_UI);
	m_pSprite = AddComponent<SpriteComponent>();
	m_pTransform->SetPosition(0.0f, 1.0f, 0.0f);
	m_pTransform->SetScale(0.5f, 0.5f, 1.0f);
}

void UI_TestObject::Uninit()
{
}

void UI_TestObject::Update()
{
}

void UI_TestObject::Draw()
{

}
