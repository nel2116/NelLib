#include "CameraManager.h"
#include "ObjectsManager.h"

void CameraManager::Init()
{
	CameraBase* camera[E_CAM_MAX] = { nullptr };
	camera[E_CAM_DEBUG] = OBJECTS_MANAGER.AddObject<CameraDebug>();
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
