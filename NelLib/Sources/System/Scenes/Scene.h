#pragma once
// ====== インクルード ======
#include <string>
#include <Windows.h>

// ====== クラスの宣言 ======
class Scene
{
public:
	Scene() {}
	~Scene() {}

	// 初期化
	virtual void Init() = 0;
	// 終了
	virtual void Uninit() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;

	// シーンの名前を取得
	std::string GetName() { return m_name; }
	// シーンの名前を設定
	void SetName(const std::string& name) { m_name = name; }

	// シーン名の表示
	void ShowName();

protected:
	// シーンの名前
	std::string m_name;

};