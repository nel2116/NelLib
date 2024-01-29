#include "testObject.h"
#include <DirectX/Renderer.h>
#include <DirectX/Sprite.h>
#include <System/Geometory.h>

#define SPRITE_DEBUG (0)
#define GEOMETORY_DEBUG (1)
#define MODEL_DEBUG (1)

TestObject::TestObject()
	: m_pModel(nullptr)
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
	m_pModel->Load("Assets/Models/eyeBat/eyebat.fbx", 0.1f);
	WARNING(!m_pModel, "モデルの読み込みに失敗しました", "");

#endif // MODEL_DEBUG
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
	RenderTarget* RTV = RENDERER.GetDefaultRTV();
	DepthStencil* DSV = RENDERER.GetDefaultDSV();
	RENDERER.SetRenderTargets(1,&RTV,DSV);			// レンダーターゲットの設定
	// モデルの描画
	m_pModel->Draw();

#endif // MODEL_DEBUG
}

void TestObject::Uninit()
{
	SAFE_DELETE(m_pModel);
}
