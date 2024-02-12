#pragma once

// ====== インクルード部 ======
#include <System/Macro.h>
#include <Windows.h>

// ====== クラス宣言 ======
class TimeManager
{
public:
	// 初期化
	void Init();
	// 更新
	void Update();
	// 終了処理
	void Finalize();

public:	// ゲッター・セッター
	// 経過時間取得
	float GetDeltaTime() const { return m_deltaTime; }
	// 経過時間取得(秒)
	float GetDeltaTimeSecond() const { return m_deltaTime * 0.001f; }
	// フレーム時間取得
	float GetFrameTime() const { return m_frameTime; }
	// フレーム数取得
	int GetFrameCount() const { return m_frameCount; }
	// FPS取得
	float GetFPS() const { return m_fps; }

	void UpdateLastTime() { m_lastTime = m_currentTime; }

private:
	DWORD m_startTime;		// 開始時間
	DWORD m_currentTime;	// 現在時間
	DWORD m_lastTime;		// 前回時間
	float m_deltaTime;		// 前回フレームからの経過時間
	float m_frameTime;		// フレーム時間
	int m_frameCount;		// フレーム数
	float m_fps;			// FPS

public:	// シングルトン
	// インスタンス取得
	static TimeManager& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = NEW TimeManager();
		}
		return *instance;
	}

	// インスタンス破棄
	static void DestroyInstance()
	{
		SAFE_DELETE(instance);
	}

private:
	static inline TimeManager* instance = nullptr;
	// コンストラクタ
	TimeManager() : m_startTime(0), m_currentTime(0), m_deltaTime(0), m_lastTime(0), m_frameTime(0), m_frameCount(0), m_fps(0) {}
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	~TimeManager() { Finalize(); }
};

// シングルトンインスタンス
#define TIME_MANAGER TimeManager::GetInstance()