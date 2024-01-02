#pragma once
// ====== �C���N���[�h�� ======
#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")

#include "../System/common.h"
#include "../System/MATRIX.h"
#include "../System/COLOR.h"
#include "VERTEX.h"
#include "VERTEX_BUFFER.h"

class RenderTarget;
class DepthStencil;
class Shader;
class MeshBuffer;

enum BlendMode
{
	BLEND_NONE,
	BLEND_ALPHA,
	BLEND_ADD,
	BLEND_ADDALPHA,
	BLEND_SUB,
	BLEND_SCREEN,
	BLEND_MAX
};

enum SamplerState
{
	SAMPLER_LINEAR,
	SAMPLER_POINT,
	SAMPLER_MAX
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
	/// <param name="fullscreen">�t���X�N���[�����ǂ���</param>
	/// <remarks>���C�u�������ŌĂ�ł���̂ŌĂԕK�v�Ȃ�</remarks>
	void Init(int baseWidth, int baseHeight,bool fullscreen);
	/// <summary>
	/// ����֐�
	/// </summary>
	/// <remarks>������s��</remarks>
	/// <remarks>���C�u�������ŌĂ�ł���̂ŌĂԕK�v�Ȃ�</remarks>
	void Release();
	void Begin();
	void End();
	void SetClearColor(float r, float g, float b, float a);

	/// <summary>
	/// �f�o�C�X�̎擾�֐�
	/// </summary>
	/// <returns>�f�o�C�X</returns>
	/// <remarks>�f�o�C�X���擾����</remarks>
	ID3D11Device* GetDevice() { return m_pDevice; }

	/// <summary>
	/// �f�o�C�X�R���e�L�X�g�̎擾�֐�
	/// </summary>
	/// <returns>�f�o�C�X�R���e�L�X�g</returns>
	/// <remarks>�f�o�C�X�R���e�L�X�g���擾����</remarks>
	ID3D11DeviceContext* GetContext() { return m_pContext; }

	/// <summary>
	/// �X���b�v�`�F�C���̎擾�֐�
	/// </summary>
	/// <returns>�X���b�v�`�F�C��</returns>
	/// <remarks>�X���b�v�`�F�C�����擾����</remarks>
	IDXGISwapChain* GetSwapChain() { return m_pSwapChain; }

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[�̎擾�֐�
	/// </summary>
	/// <returns>�����_�[�^�[�Q�b�g�r���[</returns>
	/// <remarks>�����_�[�^�[�Q�b�g�r���[���擾����</remarks>
	RenderTarget* GetDefaultRTV(){ return m_pRTV; }

	/// <summary>
	/// �[�x�X�e���V���r���[�̎擾�֐�
	/// </summary>
	/// <returns>�[�x�X�e���V���r���[</returns>
	/// <remarks>�[�x�X�e���V���r���[���擾����</remarks>
	DepthStencil* GetDefaultDSV(){ return m_pDSV; }

	/// <summary>
	/// �����_�[�^�[�Q�b�g�̐ݒ�֐�
	///	</summary>
	/// <param name="num">�����_�[�^�[�Q�b�g�̐�</param>
	/// <param name="ppViews">�����_�[�^�[�Q�b�g�r���[</param>
	/// <param name="pView">�[�x�X�e���V���r���[</param>
	/// <remarks>�����_�[�^�[�Q�b�g��ݒ肷��</remarks>
	void SetRenderTargets(UINT num, RenderTarget** ppViews, DepthStencil* pView);

	/// <summary>
	/// �J�����O���[�h�̐ݒ�֐�
	/// </summary>
	/// <param name="cull">�J�����O���[�h</param>
	/// <remarks>�J�����O���[�h��ݒ肷��</remarks>
	void SetCullingMode(D3D11_CULL_MODE cull);

	/// <summary>
	/// �u�����h�X�e�[�g�̐ݒ�֐�
	///	</summary>
	/// <param name="blend">�u�����h���[�h</param>
	/// <remarks>�u�����h�X�e�[�g��ݒ肷��</remarks>
	void SetBlendMode(BlendMode blend);

	/// <summary>
	/// �T���v���[�X�e�[�g�̐ݒ�֐�
	/// </summary>
	/// <param name="state">�T���v���[�X�e�[�g</param>
	/// <remarks>�T���v���[�X�e�[�g��ݒ肷��</remarks>
	void SetSamplerState(SamplerState state);

	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }

	void rect(float px, float py, float w, float h, float rad, float z);

private:	// ----- �����o�֐� -----
	void CreateRectBuffer();
	void CreateDefaultShader();

private:	// ----- �����o�ϐ� -----
	// DirectX11�֘A
	ID3D11Device* m_pDevice = nullptr;			            // �f�o�C�X
	ID3D11DeviceContext* m_pContext = nullptr;	            // �f�o�C�X�R���e�L�X�g
	IDXGISwapChain* m_pSwapChain = nullptr;		            // �X���b�v�`�F�C��
	DXGI_SAMPLE_DESC MSAA = { 0,0 };			            // MSAA�ݒ�
	RenderTarget* m_pRTV = nullptr;							// �����_�[�^�[�Q�b�g�r���[
	DepthStencil* m_pDSV = nullptr;							// �[�x�X�e���V���r���[
	ID3D11BlendState* m_pBlendState[BLEND_MAX];	            // �u�����h�X�e�[�g
	ID3D11RasterizerState* m_pRasterizerState[3];			// ���X�^���C�U�[�X�e�[�g
	ID3D11SamplerState* m_pSamplerState[SAMPLER_MAX];		// �T���v���[�X�e�[�g
	float m_ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };		// �N���A�J���[
	float m_Width = 0.0f;									// ��
	float m_Height = 0.0f;									// ����
	std::vector<MeshBuffer*> m_MeshBuffer;					// ���b�V���o�b�t�@

	// ���ʎg�p�}�g���b�N�X
	MATRIX m_World;											// ���[���h�s��
	MATRIX m_Proj;											// �ˉe�s��
	
	// �f�t�H���g�l
	COLOR m_FillColor;										// �h��Ԃ��F

	// �f�t�H���g�V�F�[�_
	Shader* m_pVS;											// ���_�V�F�[�_
	Shader* m_pPS;											// �s�N�Z���V�F�[�_

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