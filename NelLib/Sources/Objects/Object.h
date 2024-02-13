#pragma once

// ====== インクルード部 ======
#include <vector>
#include <algorithm>
#include <Components/Component.h>
#include <System/Macro.h>
#include <Objects/Camera/CameraBase.h>

// ゲームオブジェクトの基底クラス
class Object
{
public:
	// コンストラクタ
	Object() : order(50), enable(true), destroy(false), parent(nullptr), camera{}

		// デストラクタ
	virtual ~Object();

	// 初期化処理
	virtual void Init() {}

	// 更新処理
	virtual void Update() {}

	// 描画処理
	virtual void Draw() {}

	// 終了処理
	virtual void Uninit() = 0;

public:	// ゲッターセッター

	// オーダーの取得
	int GetOrder() { return order; }
	// オーダーの設定
	void SetOrder(int order) { this->order = order; }
	// 有効かどうかの取得
	bool IsEnable() { return enable; }
	// 有効かどうかの設定
	void SetEnable(bool enable) { this->enable = enable; }
	// 破棄するかどうかの取得
	bool IsDestroy() { return destroy; }
	// 破棄するかどうかの設定
	void Destroy() { destroy = true; enable = false; }
	// カメラの設定
	void SetCamera(CameraBase* camera) { this->camera = camera; }

public:	// 親子関係
	// 親オブジェクトの取得
	Object* GetParent() { return parent; }
	// 親オブジェクトの設定
	void SetParent(Object* parent) { this->parent = parent; }
	// 親子関係の破棄
	void RemoveParent() { parent = nullptr; }

public:	// コンポーネント関連

	// コンポーネントの追加
	template <typename T>
	T* AddComponent()
	{
		// すでに同じコンポーネントがアタッチされている場合は追加しない
		for (auto component : components)
		{
			T* castComponent = dynamic_cast<T*>(component);
			if (castComponent != nullptr)
			{
				return castComponent;
			}
		}
		// 新たに追加されたコンポーネントを一時的に保持する
		T* newComponent = NEW T(this);
		newComponents.push_back(newComponent);
		return newComponent;
	}

	// コンポーネントの取得
	template <typename T>
	T* GetComponent()
	{
		for (auto component : components)
		{
			T* castComponent = dynamic_cast<T*>(component);
			if (castComponent != nullptr)
			{
				return castComponent;
			}
		}
		return nullptr;
	}

	// コンポーネントの更新
	void UpdateComponents();

	// コンポーネントの描画
	void DrawComponents();

private:
	// コンポーネントをオーダーの順番に並び替える
	void SortComponents();

private:	// メンバ変数
	// コンポーネントのリスト
	std::vector<Component*> components;
	// コンポーネントの更新中に配列が変更されるとイテレータが無効になるので、新たに追加されたコンポーネントを一時的に保持する
	std::vector<Component*> newComponents;
	int order;		// 各オブジェクトの処理する順番,値が小さいほど早く処理される
	bool enable;	// 有効かどうか
	bool destroy;	// 破棄するかどうか
	CameraBase* camera;	// カメラ
	Object* parent;	// 親オブジェクト
};