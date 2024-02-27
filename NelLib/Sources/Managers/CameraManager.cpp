#include "CameraManager.h"
#include "ObjectsManager.h"
#include <Objects/Camera/CameraDebug.h>
#include <Objects/Camera/CameraUI.h>
#include <Objects/Camera/CameraPlayer.h>

void CameraManager::Init()
{
	CameraBase* camera[E_CAM_MAX] = {};
	camera[E_CAM_DEBUG] = OBJECTS_MANAGER.AddObjects<CameraDebug>();
	camera[E_CAM_UI] = OBJECTS_MANAGER.AddObjects<CameraUI>();
	camera[E_CAM_PLAYER] = OBJECTS_MANAGER.AddObjects<CameraPlayer>();
	for (int i = 0; i < E_CAM_MAX; ++i)
	{
		m_Cameras.push_back(camera[i]);
	}
	m_nowCamera = E_CAM_PLAYER;
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

