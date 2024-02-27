#pragma once

// ====== インクルード部 ======
#include <windows.h>
#include <typeinfo>
#include <vector>
#include <Objects/Object.h>
#include <System/Macro.h>
#include <System/Singleton.h>
#include "CameraManager.h"

// ====== 前方宣言 ======

// ====== クラスの宣言 ======
class ObjectsManager : public Singleton<ObjectsManager>
{
public:
	// デストラクタ
	~ObjectsManager() { Uninit(); }

	// 初期化処理
	void Init()
	{
		// オブジェクトの初期化
		for (auto object : objects)
		{
			object->Init();
		}
	}

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// 終了処理
	void Uninit();

	// オブジェクトの追加
	template <typename T>
	T* AddObjects()
	{
		T* object = nullptr;
		// Objectクラスを継承していないクラスは追加できない
		if (!typeid(T).before(typeid(Object*)))
		{
			// エラーメッセージを表示
			//typeidから型情報を取得してエラーとして出力する
			std::string typeName = typeid(T).name();
			std::string error = "エラー: " + typeName + " はObjectクラスを継承していません。";
			OutputDebugStringA(error.c_str());
			return object;
		}
		object = NEW T();
		newObjects.push_back(object);
		return object;
	}

	// オブジェクトの取得
	template <typename T>
	T* GetObjects()
	{
		for (auto object : objects)
		{
			T* castObject = dynamic_cast<T*>(object);
			if (castObject != nullptr)
			{
				return castObject;
			}
		}
		// 見つからなかった場合は追加予定のオブジェクトを検索
		for (auto object : newObjects)
		{
			T* castObject = dynamic_cast<T*>(object);
			if (castObject != nullptr)
			{
				return castObject;
			}
		}
		// それでも見つからなかった場合はnullptrを返す
		return nullptr;
	}

private:
	// オブジェクトをソート
	void SortObjects();

private:
	// オブジェクトのリスト
	std::vector<Object*> objects;
	// 更新中に追加されたオブジェクトのリスト
	std::vector<Object*> newObjects;

public:	// シングルトン関連
	friend Singleton<ObjectsManager>;
	ObjectsManager() {}
};

// シングルトンのインスタンスを取得するマクロ
#define OBJECTS_MANAGER ObjectsManager::GetInstance()