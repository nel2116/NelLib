#pragma once
// ====== インクルード部 ======
#include <System/Singleton.h>
#include <System/Model.h>
#include <vector>

// ====== クラスの宣言 ======
class ModelManager : public Singleton<ModelManager>
{
public:
	enum ModelType
	{
		MODEL_PLAYER,
		MODEL_ENEMY,
		MODEL_STAIRS,

		MODEL_MAX,
	};

public:
	// デストラクタ
	~ModelManager() { Uninit(); }

	// 初期化
	void Init();

	// 終了
	void Uninit();

	// モデルの取得
	Model* GetModel(ModelType type);

private:
	// モデルのリスト
	std::vector<Model*> m_ModelList;

private:	// シングルトン関連
	friend Singleton<ModelManager>;
	ModelManager() {}

};
// インスタンスを獲得するマクロ
#define MODEL_MANAGER ModelManager::GetInstance()