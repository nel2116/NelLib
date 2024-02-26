#pragma once
// ====== インクルード ======
#include <map>
#include <System/Singleton.h>
#include <System/Scenes/Scene.h>
#include <Objects/Fade.h>

// ====== クラスの宣言 ======

class SceneManager : public Singleton<SceneManager>
{
public:
	// デストラクタ
	~SceneManager() { Uninit(); }

	void Init();	// 初期化処理
	void Uninit();	// 終了処理
	void Update();	// 更新処理
	void Draw();	// 描画処理

	// シーンの追加
	void AddScene(Scene* pScene);
	// シーン名でシーンを変更
	void ChangeScene(const std::string& name);
	// シーンの取得
	Scene* GetScene() { return m_pNowScene; }
	// シーン名からシーンの取得
	Scene* GetScene(const std::string& name) { return m_Scenes[name]; }
	// シーン名の取得
	std::string GetSceneName() { return m_pNowScene->GetName(); }
	// シーンリセット
	void ResetScene();

private:	// メンバ変数
	Scene* m_pNowScene;		// 現在のシーン
	Scene* m_pNextScene;	// 次のシーン
	std::map<std::string, Scene*> m_Scenes;	// シーンのリスト
	Fade* m_pFade;	// フェード

private:	// シングルトン関連
	friend Singleton<SceneManager>;
	SceneManager() : m_pNowScene(nullptr), m_pNextScene(nullptr), m_pFade(nullptr) {}
};
// シーンマネージャのインスタンスの取得
#define SCENE_MANAGER SceneManager::GetInstance()