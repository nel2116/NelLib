#pragma once

// ====== インクルード部 ======
#include <vector>
#include <System/Singleton.h>
#include <Objects/Camera/CameraBase.h>

// ====== クラスの定義 ======
class CameraManager : public Singleton<CameraManager>
{
public:	// 定数定義
	enum CameraType
	{
		E_CAM_DEBUG,	// デバッグカメラ
		E_CAM_UI,		// UIカメラ
		E_CAM_MAX,		// カメラの最大数
	};

public:	// メンバ関数
	~CameraManager() { Uninit(); }	// デストラクタ
	void Init();	// 初期化処理
	void Uninit();	// 終了処理

	CameraBase* GetCamera(CameraType type);	// カメラの取得
	CameraBase* GetNowCamera();	// 現在のカメラの取得
	void SetNowCamera(CameraType type);	// 現在のカメラの設定

private:	// メンバ変数
	// カメラのリスト
	std::vector<CameraBase*> m_Cameras;
	int m_nowCamera;	// 現在のカメラ

private:	// シングルトン関連
	friend Singleton<CameraManager>;
	CameraManager() : m_nowCamera(0) {}
};

// カメラマネージャのインスタンスの取得
#define CAMERA_MANAGER CameraManager::GetInstance()