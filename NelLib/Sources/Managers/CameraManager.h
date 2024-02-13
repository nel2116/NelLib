#pragma once

// ====== インクルード部 ======
#include <vector>
#include <Objects/Camera/CameraBase.h>
#include <Objects/Camera/CameraDebug.h>

// ====== クラスの定義 ======
class CameraManager
{
public:	// 定数定義
	enum CameraType
	{
		E_CAM_DEBUG,	// デバッグカメラ
		E_CAM_MAX,		// カメラの最大数
	};

public:	// メンバ関数
	void Init();	// 初期化処理
	void Uninit();	// 終了処理

	CameraBase* GetCamera(CameraType type);	// カメラの取得
	CameraBase* GetNowCamera();	// 現在のカメラの取得
	void SetNowCamera(CameraType type);	// 現在のカメラの設定

private:	// メンバ変数
	// カメラのリスト
	std::vector<CameraBase*> m_Cameras;
	int m_nowCamera;	// 現在のカメラ

public:	// シングルトン関連

	// インスタンスの取得
	static CameraManager& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = NEW CameraManager();
		}
		return *instance;
	}

	// インスタンスの破棄
	static void DestroyInstance()
	{
		SAFE_DELETE(instance);
	}

private:
	static inline CameraManager* instance = nullptr;
	CameraManager() : m_nowCamera(0) {}
	CameraManager(const CameraManager& obj) = delete;
	CameraManager& operator=(const CameraManager& obj) = delete;
};

#define CAMERA_MANAGER CameraManager::GetInstance()	// シングルトンインスタンスの取得用マクロ