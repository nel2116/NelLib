#ifndef ___TEST_OBJECT_H___
#define ___TEST_OBJECT_H___
#include <System/Model.h>

// クラス定義
class TestObject
{
public:
	// コンストラクタ
	TestObject();

	// デストラクタ
	~TestObject();

	// メンバ関数
	// 初期化
	void Init();
	void Update();
	void Draw();
	void Uninit();

private:
// メンバ変数
	Model* m_pModel;
};

#endif // !___TEST_OBJECT_H___
