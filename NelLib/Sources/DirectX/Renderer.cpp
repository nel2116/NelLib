#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include "MeshBuffer.h"
#include <System/window.h>


void Renderer::Init(int baseWidth, int baseHeight, bool fullscreen)
{
	m_FillColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	//��ƂȂ镝�ƍ���
	if (baseWidth == 0 || baseHeight == 0) {
		m_Width = (float)ClientWidth;
		m_Height = (float)ClientHeight;
	}
	else {
		m_Width = (float)baseWidth;
		m_Height = (float)baseHeight;
	}
	HRESULT	hr = E_FAIL;
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));						    // �[���N���A
	sd.BufferDesc.Width = m_Width;						    // �o�b�N�o�b�t�@�̕�
	sd.BufferDesc.Height = m_Height;					    // �o�b�N�o�b�t�@�̍���
	sd.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;	// �o�b�N�o�b�t�@�t�H�[�}�b�g(R,G,B,A)
	sd.SampleDesc.Count = 1;							    // �}���`�T���v���̐�
	sd.BufferDesc.RefreshRate.Numerator = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	    // �o�b�N�o�b�t�@�̎g�p���@
	sd.BufferCount = 1;									    // �o�b�N�o�b�t�@�̐�
	sd.OutputWindow = FindWindow("GameWindow", NULL);;	    // �֘A�t����E�C���h�E
	sd.Windowed = fullscreen ? FALSE : TRUE;				// �E�C���h�E���[�h
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;				// �o�b�N�o�b�t�@�̌������@
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// �t���X�N���[���؂�ւ��̋���

	// �h���C�o�̎��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPU�ŕ`��
		D3D_DRIVER_TYPE_WARP,		// �����x(�ᑬ
		D3D_DRIVER_TYPE_REFERENCE,	// CPU�ŕ`��
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);	// �h���C�o�̐�

	UINT createDeviceFlags = 0;

#ifndef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;	// �f�o�b�O���C���[��L���ɂ���
#endif // !_DEBUG



	// �@�\���x��
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,		// DirectX11.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_11_0,		// DirectX11�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_10_0,		// DirectX10�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_3,		// DirectX9.3�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_2,		// DirectX9.2�Ή�GPU���x��
		D3D_FEATURE_LEVEL_9_1		// Direct9.1�Ή�GPU���x��
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					// �f�B�X�v���C�f�o�C�X�̃A�_�v�^�iNULL�̏ꍇ�ŏ��Ɍ��������A�_�v�^�j
			driverType,				// �f�o�C�X�h���C�o�̃^�C�v
			NULL,					// �\�t�g�E�F�A���X�^���C�U���g�p����ꍇ�Ɏw�肷��
			createDeviceFlags,		// �f�o�C�X�t���O
			featureLevels,			// �@�\���x��
			numFeatureLevels,		// �@�\���x����
			D3D11_SDK_VERSION,		// 
			&sd,					// �X���b�v�`�F�C���̐ݒ�
			&m_pSwapChain,			// IDXGIDwapChain�C���^�t�F�[�X	
			&m_pDevice,				// ID3D11Device�C���^�t�F�[�X
			&featureLevel,		// �T�|�[�g����Ă���@�\���x��
			&m_pContext);		// �f�o�C�X�R���e�L�X�g
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	WARNINGHR(hr, "DirectX11�f�o�C�X�̍쐬�Ɏ��s���܂���");

	//--- �����_�[�^�[�Q�b�g�ݒ�
	m_pRTV = NEW RenderTarget();
	hr = m_pRTV->CreateFromScreen();
	WARNINGHR(hr, "�����_�[�^�[�Q�b�g�̍쐬�Ɏ��s���܂���");
	m_pDSV = NEW DepthStencil();
	WARNINGHR(hr = m_pDSV->Create(m_pRTV->GetWidth(), m_pRTV->GetHeight(), false), "�[�x�X�e���V���̍쐬�Ɏ��s���܂���");
	SetRenderTargets(1, &m_pRTV, nullptr);


	//--- �J�����O�ݒ�
	D3D11_RASTERIZER_DESC rasterizer = {};
	D3D11_CULL_MODE cull[] = {
		D3D11_CULL_NONE,
		D3D11_CULL_FRONT,
		D3D11_CULL_BACK
	};
	rasterizer.FillMode = D3D11_FILL_SOLID;		// �|���S���̓h��Ԃ�
	rasterizer.FrontCounterClockwise = false;	// �����v��肪�\��
	rasterizer.DepthBias = 0;					// �[�x�o�C�A�X
	rasterizer.DepthBiasClamp = 0.0f;			// �[�x�o�C�A�X�̃N�����v
	rasterizer.SlopeScaledDepthBias = 0.0f;		// �X���[�v�X�P�[���t���[�x�o�C�A�X
	rasterizer.DepthClipEnable = true;			// �[�x�N���b�s���O�̗L��
	rasterizer.ScissorEnable = false;			// �V�U�[��`�̗L��
	rasterizer.MultisampleEnable = false;		// �}���`�T���v�����O�̗L��
	rasterizer.AntialiasedLineEnable = false;	// �A���`�G�C���A�X���̗L��

	for (int i = 0; i < 3; ++i)
	{
		rasterizer.CullMode = cull[i];
		hr = m_pDevice->CreateRasterizerState(&rasterizer, &m_pRasterizerState[i]);
		WARNINGHR(hr, "���X�^���C�U�[�X�e�[�g�̍쐬�Ɏ��s���܂���");
	}
	SetCullingMode(D3D11_CULL_BACK);

	//--- �[�x�e�X�g


	//--- �A���t�@�u�����f�B���O
	// https://pgming-ctrl.com/directx11/blend/
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	D3D11_BLEND blend[BLEND_MAX][2] = {
		{D3D11_BLEND_ONE, D3D11_BLEND_ZERO},
		{D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA},
		{D3D11_BLEND_ONE, D3D11_BLEND_ONE},
		{D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ONE},
		{D3D11_BLEND_ZERO, D3D11_BLEND_INV_SRC_COLOR},
		{D3D11_BLEND_INV_DEST_COLOR, D3D11_BLEND_ONE},
	};
	for (int i = 0; i < BLEND_MAX; ++i)
	{
		blendDesc.RenderTarget[0].SrcBlend = blend[i][0];
		blendDesc.RenderTarget[0].DestBlend = blend[i][1];
		hr = m_pDevice->CreateBlendState(&blendDesc, &m_pBlendState[i]);
		WARNINGHR(hr, "�u�����h�X�e�[�g�̍쐬�Ɏ��s���܂���");
	}
	SetBlendMode(BLEND_ALPHA);

	// �T���v���[
	D3D11_SAMPLER_DESC samplerDesc = {};
	D3D11_FILTER filter[] = {
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_FILTER_MIN_MAG_MIP_POINT,
	};
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	for (int i = 0; i < SAMPLER_MAX; ++i)
	{
		samplerDesc.Filter = filter[i];
		hr = m_pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState[i]);
		WARNINGHR(hr, "�T���v���[�X�e�[�g�̍쐬�Ɏ��s���܂���");
	}
	SetSamplerState(SAMPLER_LINEAR);

	// �N���A�J���[�̐ݒ�
//	SetClearColor(0.3f, 0.6f, 1.0f, 1.0f);
	SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::Release()
{
	// �f�o�C�X�̉��
	SAFE_DELETE(m_pDSV);
	SAFE_DELETE(m_pRTV);
	for (int i = 0; i < SAMPLER_MAX; ++i)
		SAFE_RELEASE(m_pSamplerState[i]);
	for (int i = 0; i < BLEND_MAX; ++i)
		SAFE_RELEASE(m_pBlendState[i]);
	for (int i = 0; i < 3; ++i)
		SAFE_RELEASE(m_pRasterizerState[i]);
	if (m_pContext)
		m_pContext->ClearState();
	SAFE_RELEASE(m_pContext);
	if (m_pSwapChain)
		m_pSwapChain->SetFullscreenState(false, NULL);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pDevice);
}

void Renderer::Begin()
{
	SetRenderTargets(1, &m_pRTV, m_pDSV);
	m_pRTV->Clear(m_ClearColor);
	m_pDSV->Clear();
}

void Renderer::End()
{
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pSwapChain->Present(0, 0);
}


void Renderer::SetClearColor(float r, float g, float b, float a)
{
	m_ClearColor[0] = r;
	m_ClearColor[1] = g;
	m_ClearColor[2] = b;
	m_ClearColor[3] = a;
}

void Renderer::SetRenderTargets(UINT num, RenderTarget** ppViews, DepthStencil* pView)
{
	static ID3D11RenderTargetView* rtvs[4];

	if (num > 4) num = 4;
	for (UINT i = 0; i < num; ++i)
		rtvs[i] = ppViews[i]->GetView();
	m_pContext->OMSetRenderTargets(num, rtvs, pView ? pView->GetView() : nullptr);

	// �r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (float)ppViews[0]->GetWidth();
	vp.Height = (float)ppViews[0]->GetHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_pContext->RSSetViewports(1, &vp);
}

void Renderer::SetCullingMode(D3D11_CULL_MODE cull)
{
	switch (cull)
	{
	case D3D11_CULL_NONE: m_pContext->RSSetState(m_pRasterizerState[0]); break;
	case D3D11_CULL_FRONT: m_pContext->RSSetState(m_pRasterizerState[1]); break;
	case D3D11_CULL_BACK: m_pContext->RSSetState(m_pRasterizerState[2]); break;
	}
}

void Renderer::SetBlendMode(BlendMode blend)
{
	if (blend < 0 || blend >= BLEND_MAX) return;
	FLOAT blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
	m_pContext->OMSetBlendState(m_pBlendState[blend], blendFactor, 0xffffffff);
}

void Renderer::SetSamplerState(SamplerState state)
{
	if (state < 0 || state >= SAMPLER_MAX) return;
	m_pContext->PSSetSamplers(0, 1, &m_pSamplerState[state]);
}

Renderer::~Renderer()
{
	Release();
}
