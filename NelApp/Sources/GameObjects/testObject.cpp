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

#if GEOMETORY_DEBUG

	// ���f���\���̂��߁A�L�����̗��n�ʂƂ��ĕό`������
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, -0.1f, 0.0f);	// �O���b�h�������ɗ���悤�Ɉړ�
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
	ModelMat[0] = m_pTransform->GetWorldMatrix();	// ���[���h�s��

	// View���
	ModelMat[1] = m_pCamera->GetViewMatrix();

	// Projection���
	ModelMat[2] = m_pCamera->GetProjectionMatrix();

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
