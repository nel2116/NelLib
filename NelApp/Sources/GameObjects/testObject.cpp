#include "testObject.h"
#include <DirectX/Renderer.h>
#include <DirectX/Sprite.h>
#include <System/Geometory.h>
#include <Objects/Camera/CameraDebug.h>

#define GEOMETORY_DEBUG (1)
#define MODEL_DEBUG (1)
#define SHADER_DEBUG (1)

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

#if GEOMETORY_DEBUG

	// モデル表示のため、キャラの立つ地面として変形させる
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, -0.1f, 0.0f);	// グリッドよりも下に来るように移動
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
	ModelMat[0] = m_pTransform->GetWorldMatrix();	// ワールド行列

	// View空間
	ModelMat[1] = m_pCamera->GetViewMatrix();

	// Projection空間
	ModelMat[2] = m_pCamera->GetProjectionMatrix();

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
