#pragma once
// ====== �C���N���[�h�� ======
#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#include "Vertex.h"
// #include "Shader.h"
#include "../System/common.h"



struct Shader
{
	Shader() {}
	~Shader() {
		SAFE_RELEASE(pVertexShader);
		SAFE_RELEASE(pPixelShader);
		SAFE_RELEASE(pInputLayout);
	}

	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11InputLayout* pInputLayout = nullptr;
};

// ====== �N���X�錾�� ======
class Renderer
{
public:		// ----- �����o�֐� -----
	/// <summary>
	/// �������֐�
	/// </summary>
	/// <remarks>���������s��</remarks>
	/// <param name="baseWidth">��</param>
	/// <param name="baseHeight">����</param>
	/// <remarks>���C�u�������ŌĂ�ł���̂ŌĂԕK�v�Ȃ�</remarks>
	void Init(int baseWidth, int baseHeight);
	/// <summary>
	/// ����֐�
	/// </summary>
	/// <remarks>������s��</remarks>
	/// <remarks>���C�u�������ŌĂ�ł���̂ŌĂԕK�v�Ȃ�</remarks>
	void Release();
	void Begin();
	void End();
	void Present();
	void SetClearColor(float r, float g, float b, float a);

	/// <summary>
	/// �f�o�C�X�̎擾�֐�
	/// </summary>
	/// <returns>�f�o�C�X</returns>
	/// <remarks>�f�o�C�X���擾����</remarks>
	ID3D11Device* GetDevice() { return m_Device; }

	/// <summary>
	/// �f�o�C�X�R���e�L�X�g�̎擾�֐�
	/// </summary>
	/// <returns>�f�o�C�X�R���e�L�X�g</returns>
	/// <remarks>�f�o�C�X�R���e�L�X�g���擾����</remarks>
	ID3D11DeviceContext* GetContext() { return m_Context; }


private:	// ----- �����o�֐� -----
	/// <summary>
	/// �f�o�C�X�̍쐬�֐�
	/// </summary>
	/// <remarks>�f�o�C�X�̍쐬���s��</remarks>
	void createDevice();

	/// <summary>
	/// �����_�[�^�[�Q�b�g�̍쐬�֐�
	/// </summary>
	/// <remarks>�����_�[�^�[�Q�b�g�̍쐬���s��</remarks>
	void createRenderTarget();

	/// <summary>
	/// �r���[�|�[�g�̐ݒ�֐�
	/// </summary>
	/// <remarks>�r���[�|�[�g�̐ݒ���s��</remarks>
	void setViewport();

	/// <summary>
	/// �[�x�X�e���V���X�e�[�g�̍쐬�֐�
	/// </summary>
	/// <remarks>�[�x�X�e���V���X�e�[�g�̍쐬���s��</remarks>
	void createDepthStencielState();

	/// <summary>
	/// �u�����h�X�e�[�g�̍쐬�֐�
	/// </summary>
	/// <remarks>�u�����h�X�e�[�g�̍쐬���s��</remarks>
	void createBlendState();

	/// <summary>
	/// ���X�^���C�U�[�X�e�[�g�̍쐬�֐�
	/// </summary>
	/// <remarks>���X�^���C�U�[�X�e�[�g�̍쐬���s��</remarks>
	void createRasterizerState();

	/// <summary>
	/// �T���v���[�X�e�[�g�̍쐬�֐�
	/// </summary>
	/// <remarks>�T���v���[�X�e�[�g�̍쐬���s��</remarks>
	void createSamplerState();

	/// <summary>
	/// �V�F�[�_�[�̐����֐�
	/// </summary>
	/// <remarks>�V�F�[�_�[�̐������s��</remarks>
	void createShaderFromRes();

	/// <summary>
	/// �萔�o�b�t�@�̐����֐�
	/// </summary>
	/// <remarks>�萔�o�b�t�@�̐������s��</remarks>
	void createConstantBuffer();

	void createTexCoordBuffer();     // �e�N�X�`�����W�o�b�t�@�̐���


	bool CompileShader(const WCHAR* vsPath, const WCHAR* psPath, Shader& outShader);

private:	// ----- �����o�ϐ� -----
	ID3D11Device* m_Device = nullptr;			            // �f�o�C�X
	ID3D11DeviceContext* m_Context = nullptr;	            // �f�o�C�X�R���e�L�X�g
	IDXGISwapChain* m_SwapChain = nullptr;		            // �X���b�v�`�F�C��
	DXGI_SAMPLE_DESC MSAA = { 0,0 };			            // MSAA�ݒ�
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;	// �����_�[�^�[�Q�b�g�r���[
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;	// �[�x�X�e���V���r���[
	ID3D11DepthStencilState* m_DepthStencilState = nullptr;	// �[�x�X�e���V���X�e�[�g
	ID3D11BlendState* m_BlendState = nullptr;	            // �u�����h�X�e�[�g
	ID3D11RasterizerState* m_RasterizerStateWire = 0;		// ���X�^���C�U�[�X�e�[�g
	ID3D11RasterizerState* m_RasterizerStateCullBack = 0;	// ���X�^���C�U�[�X�e�[�g
	ID3D11RasterizerState* m_RasterizerStateCullNone = 0;	// ���X�^���C�U�[�X�e�[�g
	ID3D11SamplerState* m_SamplerStateClamp = 0;			// �T���v���[�X�e�[�g	
	ID3D11SamplerState* m_SamplerStateWrap = 0;				// �T���v���[�X�e�[�g
	Triangle m_testTriangle;									// �O�p�`
	// ID3D11VertexShader* m_VertexShader = nullptr;			// ���_�V�F�[�_�[
	// ID3D11PixelShader* m_PixelShader = nullptr;				// �s�N�Z���V�F�[�_�[
	// ID3D11InputLayout* m_VertexLayout = nullptr;				// ���_���C�A�E�g
	// ID3D11Buffer* m_ConstantBuffer = nullptr;				// �萔�o�b�t�@
	float m_ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };		// �N���A�J���[
	// VertexShader* m_pVS;									// ���_�V�F�[�_�[
	// PixelShader* m_pPS;										// �s�N�Z���V�F�[�_�[
	Shader m_testShader;

	float m_Width = 0.0f;									// ��
	float m_Height = 0.0f;									// ����

public:		// �ȉ��V���O���g���֘A
	~Renderer();
	/// <summary>
	/// �����_���[�̃C���X�^���X���擾����֐�
	/// </summary>
	/// <returns>�����_���[�̃C���X�^���X</returns>
	/// <remarks>���̊֐����ĂԂƁA�����_���[�̃C���X�^���X���擾�ł���</remarks>
	static Renderer& GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Renderer();
		}
		return *m_instance;
	}

	/// <summary>
	/// �����_���[�̃C���X�^���X��j������֐�
	/// </summary>
	static void DestroyInstance()
	{
		SAFE_DELETE(m_instance);
	}

private:
	// �B��̃C���X�^���X�p�|�C���^
	static inline Renderer* m_instance = nullptr;
	Renderer() {}
};

#define RENDERER Renderer::GetInstance()