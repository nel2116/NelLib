#pragma once

// ====== インクルード部 ======

class Object;

// 各振る舞いを実装するコンポーネントの基底クラス
class Component
{
public:
	// コンストラクタ
	Component(Object* owner) : owner(owner), order(50), enable(true), destroy(false) {}

	// デストラクタ
	virtual ~Component() {}

	// 初期化処理
	virtual void Init() = 0;

	// 更新処理
	virtual void Update() {}

	// 描画処理
	virtual void Draw() {}

	// 終了処理
	virtual void Uninit() = 0;

	// オーダーの取得
	int GetOrder() { return order; }
	// オーダーの設定
	void SetOrder(int order) { this->order = order; }

	// 有効かどうかの取得
	bool IsEnable() { return enable; }
	// 有効かどうかの設定
	void SetEnable(bool enable) { this->enable = enable; }

	// オーナーオブジェクトの取得
	Object* GetOwner() { return owner; }

	// 破棄するかどうかの取得
	bool IsDestroy() { return destroy; }
	// 破棄するかどうかの設定
	void Destroy() { destroy = true; enable = false; }


private:
	Object* owner;	// オーナーオブジェクト
	int order;		// 各コンポーネントの処理する順番,値が小さいほど早く処理される
	bool enable;	// 有効かどうか
	bool destroy;	// 破棄するかどうか
};