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
	// ���f���̓ǂݍ���
	m_pModel = new Model();
	WARNINGHR(m_pModel->Load("Assets/Models/eyeBat/eyebat.fbx", 0.1f), "���f���̓ǂݍ��݂Ɏ��s���܂���");

#endif // MODEL_DEBUG
#if SHADER_DEBUG
	m_pVS = new VertexShader();
	WARNINGHR(m_pVS->Load("../NelLib/Assets/Shaders/VS_Model.cso"), "�V�F�[�_�̓ǂݍ��݂Ɏ��s���܂���");
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

	Sprite::SetSize(VECTOR2(0.5f, 0.5f));	// �T�C�Y�̐ݒ�
	Sprite::SetTexture(nullptr);			// �e�N�X�`���̐ݒ�
	Sprite::Draw();							// �`��

#endif // SPRITE_DEBUG
#if GEOMETORY_DEBUG

	// ���f���\���̂��߁A�L�����̗��n�ʂƂ��ĕό`������
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, -0.5f, 0.0f);	// �O���b�h�������ɗ���悤�Ɉړ�
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(10.0f, 0.1f, 10.0f);	// �n�ʂƂȂ�悤�ɁA�O�㍶�E�ɍL���A�㉺�ɋ�������
	DirectX::XMMATRIX mat = S * T;			// ���ׂĂ̍s����܂Ƃ߂�v�Z
	mat = DirectX::XMMatrixTranspose(mat);	// �V�F�[�_�ɓn���O�Ɏ��s���鏈��
	DirectX::XMFLOAT4X4 fmat;				// �s��̊i�[��
	DirectX::XMStoreFloat4x4(&fmat, mat);	// mat��fmat�Ɋi�[���鏈��
	Geometory::SetWorld(fmat);				// �{�b�N�X�ɕϊ��s���ݒ�
	Geometory::DrawBox();					// �{�b�N�X��`��

#endif // GEOMETORY_DEBUG
#if MODEL_DEBUG
	// Warld���
	DirectX::XMFLOAT4X4 ModelMat[3] = {};			// �s��̐錾
	DirectX::XMMATRIX Trans = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);	// �ړ��s��
	Trans = DirectX::XMMatrixTranspose(Trans);		// �]�u����
	DirectX::XMStoreFloat4x4(&ModelMat[0], Trans);	// Trans��mat[0]�Ɋi�[

	// View���
	ModelMat[1] = m_pCamera->GetTransposedViewMatrix();

	// Projection���
	ModelMat[2] = m_pCamera->GetTransposedProjectionMatrix();

	// �V�F�[�_�ɍs���n��
	m_pVS->WriteBuffer(0, ModelMat);

	RenderTarget* RTV = RENDERER.GetDefaultRTV();
	DepthStencil* DSV = RENDERER.GetDefaultDSV();
	RENDERER.SetRenderTargets(1, &RTV, DSV);			// �����_�[�^�[�Q�b�g�̐ݒ�
	// ���f���̕`��
	m_pModel->Draw();

#endif // MODEL_DEBUG
}

void TestObject::Uninit()
{
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pVS);
}
