#include "testObject.h"
#include "../../NelLib/Source/DirectX/Sprite.h"

TestObject::TestObject()
{
}

TestObject::~TestObject()
{
}

void TestObject::Init()
{
}

void TestObject::Update()
{
}

void TestObject::Draw()
{
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

	Sprite::SetSize(DirectX::XMFLOAT2(0.5f, 0.5f));
	Sprite::SetTexture(nullptr);			//
	Sprite::Draw();
}

void TestObject::Uninit()
{
}
