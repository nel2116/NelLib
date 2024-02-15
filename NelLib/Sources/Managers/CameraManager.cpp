#include "CameraManager.h"
#include "ObjectsManager.h"
#include <Objects/Camera/CameraDebug.h>
#include <Objects/Camera/CameraUI.h>

void CameraManager::Init()
{
	CameraBase* camera[E_CAM_MAX] = {};
	camera[E_CAM_DEBUG] = OBJECTS_MANAGER.AddObject<CameraDebug>();
	camera[E_CAM_UI] = OBJECTS_MANAGER.AddObject<CameraUI>();
	for (int i = 0; i < E_CAM_MAX; ++i)
	{
		m_Cameras.push_back(camera[i]);
	}
}

void CameraManager::Uninit()
{
	// カメラはオブジェクトマネージャでデリートされるのでここではリストのクリアだけしておく
	m_Cameras.clear();
}

CameraBase* CameraManager::GetCamera(CameraType type)
{
	return m_Cameras[type];
}

CameraBase* CameraManager::GetNowCamera()
{
	return m_Cameras[m_nowCamera];
}

void CameraManager::SetNowCamera(CameraType type)
{
	m_nowCamera = type;
}

