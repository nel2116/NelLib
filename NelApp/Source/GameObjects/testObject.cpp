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
	// World���
	DirectX::XMMATRIX mat[3] = {};			// �s��̐錾
	mat[0] = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	mat[0] = DirectX::XMMatrixTranspose(mat[0]);	// �V�F�[�_�ɓn���O�Ɏ��s���鏈��
	DirectX::XMFLOAT4X4 fmat;				// �s��̊i�[��
	DirectX::XMStoreFloat4x4(&fmat, mat[0]);	// mat��fmat�Ɋi�[���鏈��
	Sprite::SetWorld(fmat);					// �s����V�F�[�_�ɓn������

	// View���
	mat[1] = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.0f, 0.0f, -3.0f, 0.0f), DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	mat[1] = DirectX::XMMatrixTranspose(mat[1]);
	DirectX::XMStoreFloat4x4(&fmat, mat[1]);
	Sprite::SetView(fmat);

	// Projection���
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
