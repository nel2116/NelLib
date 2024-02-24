#pragma once
// ====== インクルード部 ======
#include <Objects/Object.h>
#include <System/Model.h>
#include <DirectX/Shader.h>

// ====== クラス宣言 ======
class Player : public Object
{

public:
	// コンストラクタ
	Player();
	// デストラクタ
	~Player();

	// 初期化
	void Init() override;

	// 終了
	void Uninit() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

private:
	// 移動
	void Move();
	float m_fSpeed;
	float m_fRotSpeed;
	Model* m_pModel;
	VertexShader* m_pVS;
};