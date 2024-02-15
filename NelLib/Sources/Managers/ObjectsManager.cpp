#include "ObjectsManager.h"
#include <Objects/Camera/CameraBase.h>

void ObjectsManager::Update()
{
	// 新たに追加されたオブジェクトを追加
	for (auto newObject : newObjects)
	{
		newObject->SetCamera(CAMERA_MANAGER.GetNowCamera());
		newObject->Init();
		objects.push_back(newObject);
	}
	newObjects.clear();

	// オブジェクトのソート
	SortObjects();

	// オブジェクトの更新
	for (auto object : objects)
	{
		// 有効でないは処理を飛ばす
		if (!object->IsEnable()) { continue; }
		object->Update();
		object->UpdateComponents();
	}
	// 破棄フラグが立っているオブジェクトを削除
	auto itr = std::partition(objects.begin(), objects.end(), [](Object* object) { return object->IsDestroy(); });
	std::for_each(objects.begin(), itr, [](Object* object) { delete object; });
	objects.erase(objects.begin(), itr);
}

void ObjectsManager::Draw()
{
	// オブジェクトの描画
	for (auto object : objects)
	{
		// 有効でないは処理を飛ばす
		if (!object->IsEnable()) { continue; }
		object->Draw();
		object->DrawComponents();
	}
}

void ObjectsManager::Uninit()
{
	// オブジェクトの終了処理
	for (auto object : objects)
	{
		object->Uninit();
		SAFE_DELETE(object);
	}
	objects.clear();
}

void ObjectsManager::SortObjects()
{
	// オブジェクトのソート
	std::sort(objects.begin(), objects.end(),
		[](Object* a, Object* b) { return a->GetOrder() < b->GetOrder(); });
}
