#include "testObject.h"
#include <DirectX/Renderer.h>
#include <DirectX/Sprite.h>
#include <System/Geometory.h>

#define SPRITE_DEBUG (0)
#define GEOMETORY_DEBUG (1)
#define MODEL_DEBUG (1)
#define SHADER_DEBUG (1)
#define ASPECT (16.0f / 9.0f)
#define RADIAN (M_PI / 180.0f)

TestObject::TestObject()
	: m_pModel(nullptr)
	, m_pVS(nullptr)
{
}

TestObject::~TestObject()
{
}

void TestObject::Init()
{
#if MODEL_DEBUG
	// モデルの読み込み
	m_pModel = new Model();
	WARNINGHR(m_pModel->Load("Assets/Models/eyeBat/eyebat.fbx", 0.1f), "モデルの読み込みに失敗しました");

#endif // MODEL_DEBUG
#if SHADER_DEBUG
	m_pVS = new VertexShader();
	WARNINGHR(m_pVS->Load("../NelLib/Assets/Shaders/VS_Model.cso"), "シェーダの読み込みに失敗しました");
	m_pModel->SetVertexShader(m_pVS);

#endif // SHADER_DEBUG

}

void TestObject::Update()
{
#if MODEL_DEBUG

#endif // MODEL_DEBUG

}

void TestObject::Draw()
{
#if SPRITE_DEBUG

	// World空間
	DirectX::XMMATRIX mat[3] = {};			// 行列の宣言
	mat[0] = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	mat[0] = DirectX::XMMatrixTranspose(mat[0]);	// シェーダに渡す前に実行する処理
	DirectX::XMFLOAT4X4 fmat;				// 行列の格納先
	DirectX::XMStoreFloat4x4(&fmat, mat[0]);	// matをfmatに格納する処理
	Sprite::SetWorld(fmat);					// 行列をシェーダに渡す処理

	// View空間
	mat[1] = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f), DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	mat[1] = DirectX::XMMatrixTranspose(mat[1]);
	DirectX::XMStoreFloat4x4(&fmat, mat[1]);
	Sprite::SetView(fmat);

	// Projection空間
	mat[2] = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), 1280.0f / 720.0f, 0.3f, 100.0f);
	mat[2] = DirectX::XMMatrixTranspose(mat[2]);
	DirectX::XMStoreFloat4x4(&fmat, mat[2]);
	Sprite::SetProjection(fmat);

	Sprite::SetSize(VECTOR2(0.5f, 0.5f));	// サイズの設定
	Sprite::SetTexture(nullptr);			// テクスチャの設定
	Sprite::Draw();							// 描画

#endif // SPRITE_DEBUG
#if GEOMETORY_DEBUG

	// モデル表示のため、キャラの立つ地面として変形させる
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, -0.5f, 0.0f);	// グリッドよりも下に来るように移動
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(10.0f, 0.1f, 10.0f);	// 地面となるように、前後左右に広く、上下に狭くする
	DirectX::XMMATRIX mat = S * T;			// すべての行列をまとめる計算
	mat = DirectX::XMMatrixTranspose(mat);	// シェーダに渡す前に実行する処理
	DirectX::XMFLOAT4X4 fmat;				// 行列の格納先
	DirectX::XMStoreFloat4x4(&fmat, mat);	// matをfmatに格納する処理
	Geometory::SetWorld(fmat);				// ボックスに変換行列を設定
	Geometory::DrawBox();					// ボックスを描画

#endif // GEOMETORY_DEBUG
#if MODEL_DEBUG
	// Warld空間
	DirectX::XMFLOAT4X4 ModelMat[3] = {};			// 行列の宣言
	DirectX::XMMATRIX Trans = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);	// 移動行列
	Trans = DirectX::XMMatrixTranspose(Trans);		// 転置処理
	DirectX::XMStoreFloat4x4(&ModelMat[0], Trans);	// Transをmat[0]に格納

	// View空間
	ModelMat[1] = m_pCamera->GetTransposedViewMatrix();

	// Projection空間
	ModelMat[2] = m_pCamera->GetTransposedProjectionMatrix();

	// シェーダに行列を渡す
	m_pVS->WriteBuffer(0, ModelMat);

	RenderTarget* RTV = RENDERER.GetDefaultRTV();
	DepthStencil* DSV = RENDERER.GetDefaultDSV();
	RENDERER.SetRenderTargets(1, &RTV, DSV);			// レンダーターゲットの設定
	// モデルの描画
	m_pModel->Draw();

#endif // MODEL_DEBUG
}

void TestObject::Uninit()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
}
