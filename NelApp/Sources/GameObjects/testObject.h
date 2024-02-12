#ifndef ___TEST_OBJECT_H___
#define ___TEST_OBJECT_H___
#include <System/Model.h>
#include <DirectX/Shader.h>
#include <Objects/Object.h>
#include <Objects/Camera/CameraBase.h>

// クラス定義
class TestObject : public Object
{
public:
	// コンストラクタ
	TestObject();

	// デストラクタ
	~TestObject();

	// メンバ関数
	// 初期化
	void Init() override;
	void Update() override;
	void Draw() override;
	void Uninit() override;

	void SetCamera(CameraBase* camera) { m_pCamera = camera; }

private:
	// メンバ変数
	Model* m_pModel;
	VertexShader* m_pVS;
	CameraBase* m_pCamera;
};

#endif // !___TEST_OBJECT_H___
