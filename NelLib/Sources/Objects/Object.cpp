#include "Object.h"
#include <System/Macro.h>

Object::Object()
	: order(50)
	, enable(true)
	, destroy(false)
	, m_pParent(nullptr)
	, m_pCamera()
	, m_pTransform(nullptr)
{
	m_pTransform = AddComponent<TransformComponent>();
}

Object::~Object()
{
	// コンポーネントの終了処理
	for (auto component : components)
	{
		component->Uninit();
		SAFE_DELETE(component);
	}
	components.clear();
}

void Object::UpdateComponents()
{
	// 新たに追加されたコンポーネントを追加
	for (auto newComponent : newComponents)
	{
		newComponent->Init();
		components.push_back(newComponent);
	}
	newComponents.clear();

	// コンポーネントのソート
	SortComponents();

	// コンポーネントの更新
	for (auto component : components)
	{
		// 有効でないは処理を飛ばす
		if (!component->IsEnable()) { continue; }
		component->Update();
	}

	// 破棄フラグが立っているコンポーネントのポインタを削除
	auto itr = std::partition(components.begin(), components.end(), [](Component* component) { return component->IsDestroy(); });
	std::for_each(components.begin(), itr, [](Component* component) { component->Uninit(); SAFE_DELETE(component); });
	components.erase(components.begin(), itr);
}

void Object::DrawComponents()
{
	// コンポーネントの描画
	for (auto component : components)
	{
		// 有効でないは処理を飛ばす
		if (!component->IsEnable()) { continue; }
		component->Draw();
	}
}

void Object::SortComponents()
{
	// コンポーネントのソート
	std::sort(components.begin(), components.end(), [](Component* a, Component* b) { return a->GetOrder() < b->GetOrder(); });
}