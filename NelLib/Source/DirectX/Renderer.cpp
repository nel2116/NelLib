#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include "Renderer.h"
#include "../System/window.h"

void Renderer::Init(int baseWidth, int baseHeight)
{
    //��ƂȂ镝�ƍ���
    if (baseWidth == 0 || baseHeight == 0) {
        m_Width = (float)ClientWidth;
        m_Height = (float)ClientHeight;
    }
    else {
        m_Width = (float)baseWidth;
        m_Height = (float)baseHeight;
    }

    createDevice();             // �f�o�C�X�̐���
    createRenderTarget();       // �����_�[�^�[�Q�b�g�̐���
    setViewport();              // �r���[�|�[�g�̐ݒ�

    createDepthStencielState(); // �[�x�X�e���V���X�e�[�g�̐���
    createBlendState();         // �u�����h�X�e�[�g�̐���
    createRasterizerState();    // ���X�^���C�U�[�X�e�[�g�̐���
    createSamplerState();       // �T���v���[�X�e�[�g�̐���

//    createShaderFromRes();      // �V�F�[�_�[�̐���
//    createConstantBuffer();     // �萔�o�b�t�@�̐���

//    createTexCoordBuffer();     // �e�N�X�`�����W�o�b�t�@�̐���
    SetClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    CompileShader(L"../NelLib/Source/HLSL/VertexShader.hlsl", L"../NelLib/Source/HLSL/PixelShader.hlsl", m_testShader);
    m_testTriangle.CreateVertexBuffer();

    // m_pVS = new VertexShader();
    // m_pPS = new PixelShader();
    // m_pVS->Load("Assets/Shader/VertexShader.cso");
    // m_pPS->Load("Assets/Shader/PixelShader.cso");


}

void Renderer::Release()
{
    // SAFE_DELETE(m_pVS);
    // SAFE_DELETE(m_pPS);
    // �f�o�C�X�̉��
	SAFE_RELEASE(m_SamplerStateClamp);
	SAFE_RELEASE(m_SamplerStateWrap);
	SAFE_RELEASE(m_RasterizerStateCullNone);
	SAFE_RELEASE(m_RasterizerStateCullBack);
	SAFE_RELEASE(m_RasterizerStateWire);
	SAFE_RELEASE(m_BlendState);
	SAFE_RELEASE(m_DepthStencilState);
	SAFE_RELEASE(m_DepthStencilView);
	SAFE_RELEASE(m_RenderTargetView);
	SAFE_RELEASE(m_SwapChain);
	SAFE_RELEASE(m_Context);
	SAFE_RELEASE(m_Device);
}

void Renderer::Begin()
{
    // �����_�[�^�[�Q�b�g�̃N���A
	m_Context->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	// �[�x�X�e���V���̃N���A
	m_Context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::End()
{
    //     m_pVS->Bind();
    //     m_pPS->Bind();

    m_Context->IASetInputLayout(m_testShader.pInputLayout);
    m_Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_Context->VSSetShader(m_testShader.pVertexShader, nullptr, 0);
    m_Context->PSSetShader(m_testShader.pPixelShader, nullptr, 0);
    m_testTriangle.Draw();
}

void Renderer::Present()
{
// �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f
	m_SwapChain->Present(0, 0);
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
    m_ClearColor[0] = r;
    m_ClearColor[1] = g;
    m_ClearColor[2] = b;
    m_ClearColor[3] = a;
}

void Renderer::createDevice()
{
    //�}���`�T���v�����O�Ή�
    //�f�o�C�X�̐���
    HRESULT hr;
    hr = D3D11CreateDevice(
        NULL,                       // �f�t�H���g�A�_�v�^�[���g�p
        D3D_DRIVER_TYPE_HARDWARE,   // �n�[�h�E�F�A�A�N�Z�����[�^���g�p
        NULL,   		            // �\�t�g�E�F�A���X�^���C�U���g�p
        0,  					    // �t���O
        NULL,   			        // �f�t�H���g�̃t�B�[�`���[���x���z����g�p
        0,  				        // �f�t�H���g�̃t�B�[�`���[���x���z��̃T�C�Y
        D3D11_SDK_VERSION,          // SDK�o�[�W����
        &m_Device,                  // �f�o�C�X
        NULL,                       // �T�|�[�g����Ă���t�B�[�`���[���x��
        &m_Context);                // �f�o�C�X�R���e�L�X�g
    WARNING(FAILED(hr), "D3D11CreateDevice", "");
    //�g�p�\��MSAA���擾
    for (int i = 0; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i++) {
        UINT Quality;
        hr = m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, i, &Quality);
        if (SUCCEEDED(hr)) {
            if (0 < Quality) {
                MSAA.Count = i;
                MSAA.Quality = Quality - 1;
            }
        }
    }
    //�C���^�[�t�F�[�X�擾
    IDXGIDevice1* hpDXGI = NULL;
    hr = m_Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&hpDXGI);
    WARNING(FAILED(hr), "QueryInterface", "");
    //�A�_�v�^�[�擾
    IDXGIAdapter* hpAdapter = NULL;
    hr = hpDXGI->GetAdapter(&hpAdapter);
    WARNING(FAILED(hr), "GetAdapter", "");
    //�t�@�N�g���[�擾
    IDXGIFactory* hpDXGIFactory = NULL;
    hr = hpAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&hpDXGIFactory);
    WARNING(FAILED(hr), "GetParent", "");
    //�X���b�v�`�F�C���쐬
    DXGI_SWAP_CHAIN_DESC hDXGISwapChainDesc;
    hDXGISwapChainDesc.BufferCount = 1;                                                     // �o�b�N�o�b�t�@�̐�
    hDXGISwapChainDesc.BufferDesc.Width = ClientWidth;                                      // �o�b�N�o�b�t�@�̕�
    hDXGISwapChainDesc.BufferDesc.Height = ClientHeight;                                    // �o�b�N�o�b�t�@�̍���
    hDXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                      // �t�H�[�}�b�g
    hDXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;                               // ���t���b�V�����[�g
    hDXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;		                        // ���t���b�V�����[�g
    hDXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;  // �X�L�������C���I�[�_�[
    hDXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;				    // �X�P�[�����O
    hDXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                       // �o�b�N�o�b�t�@�̎g�p�@
    hDXGISwapChainDesc.OutputWindow = FindWindow("GameWindow", NULL);                       // �o�͐�̃E�B���h�E�n���h��
    hDXGISwapChainDesc.Windowed = TRUE;								                        // �E�B���h�E���[�h
    hDXGISwapChainDesc.SampleDesc = MSAA;								                    // �}���`�T���v�����O
    hDXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;			                    // �X���b�v�G�t�F�N�g
    hDXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                      // �t���O
#ifndef _DEBUG//�����[�X���[�h�̎�
    if (Windowed == false) {
        hDXGISwapChainDesc.Windowed = FALSE;
    }
#endif
    hr = hpDXGIFactory->CreateSwapChain(m_Device, &hDXGISwapChainDesc, &m_SwapChain);
    WARNING(FAILED(hr), "CreateSwapChain", "");

    hpDXGI->Release();
    hpAdapter->Release();
    hpDXGIFactory->Release();
}

void Renderer::createRenderTarget()
{
    //�}���`�T���v�����O�Ή�
// Create a render target view
    ID3D11Texture2D* backBuffer = NULL; // �o�b�N�o�b�t�@
    // �o�b�N�o�b�t�@���擾
    HRESULT hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    WARNING(FAILED(hr), "can't Get BackBuffer", "");
    // �����_�[�^�[�Q�b�g�r���[���쐬
    hr = m_Device->CreateRenderTargetView(backBuffer, NULL, &m_RenderTargetView);
    backBuffer->Release();
    WARNING(FAILED(hr), "can't Create RenderTargetView", "");

    // Create a depth stencil texture
    D3D11_TEXTURE2D_DESC depthStencilTextureDesc;                           
    ZeroMemory(&depthStencilTextureDesc, sizeof(depthStencilTextureDesc));  // �\���̂̏�����
    depthStencilTextureDesc.Width = ClientWidth;                            // ��
    depthStencilTextureDesc.Height = ClientHeight;  				        // ����
    depthStencilTextureDesc.MipLevels = 1;                                  // �~�b�v�}�b�v��
    depthStencilTextureDesc.ArraySize = 1;                                  // �z��T�C�Y
    depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;         // �t�H�[�}�b�g
    depthStencilTextureDesc.SampleDesc = MSAA;                              // �}���`�T���v�����O
    depthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;                    // �g�p�@
    depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;           // �o�C���h�t���O
    depthStencilTextureDesc.CPUAccessFlags = 0; 			                // CPU�A�N�Z�X�t���O
    depthStencilTextureDesc.MiscFlags = 0; 				                    // �~�X�t���O
    ID3D11Texture2D* depthStencilTexture = 0;                               // �[�x�X�e���V���e�N�X�`��
    hr = m_Device->CreateTexture2D(&depthStencilTextureDesc, NULL, &depthStencilTexture);
    WARNING(FAILED(hr), "can't Create depth stencil texture", "");

    // Create a depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;                 
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));        // �\���̂̏�����
    depthStencilViewDesc.Format = depthStencilTextureDesc.Format;           // �t�H�[�}�b�g
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;   // �r���[�̎���
    depthStencilViewDesc.Texture2D.MipSlice = 0;    	                    // �~�b�v�X���C�X
    hr = m_Device->CreateDepthStencilView(depthStencilTexture, &depthStencilViewDesc, &m_DepthStencilView);
    WARNING(FAILED(hr), "can't Create DepthStencilView", "");
    SAFE_RELEASE(depthStencilTexture);

    // Set RenderTarget
    m_Context->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
}

void Renderer::setViewport()
{
    D3D11_VIEWPORT vp;
    float aspect = m_Width / m_Height;      // �A�X�y�N�g��
    if ((float)ClientWidth / ClientHeight >= aspect) {
        float width = ClientHeight * aspect;        // ����
        float left = (ClientWidth - width) / 2.0f;  // ���[
        vp.Width = width;                           // ����
        vp.Height = (float)ClientHeight;            // �c��
        vp.MinDepth = 0.0f;                         // �ŏ��[�x
        vp.MaxDepth = 1.0f;                         // �ő�[�x
        vp.TopLeftX = left; 			            // ���[
        vp.TopLeftY = 0;                            // ��[
        m_Context->RSSetViewports(1, &vp);
    }
    else {
        float height = ClientWidth / aspect;        // �c��
        float top = (ClientHeight - height) / 2.0f; // ��[
        vp.Width = (float)ClientWidth;              // ����
        vp.Height = height;     	                // �c��  
        vp.MinDepth = 0.0f;                         // �ŏ��[�x
        vp.MaxDepth = 1.0f; 					    // �ő�[�x
        vp.TopLeftX = 0;    			            // ���[
        vp.TopLeftY = top;  			            // ��[
        m_Context->RSSetViewports(1, &vp);  
    }
}

void Renderer::createDepthStencielState()
{
    // Create depth stencil state
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    depthStencilDesc.DepthEnable = TRUE;                            // �[�x�e�X�g��L���ɂ���
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // �[�x�������݃}�X�N
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;       // �[�x��r�֐�
    depthStencilDesc.StencilEnable = FALSE;						    // �X�e���V���e�X�g��L���ɂ���
    HRESULT hr = m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);    
    WARNING(FAILED(hr), "Error", "");
    m_Context->OMSetDepthStencilState(m_DepthStencilState, 0);
}

void Renderer::createBlendState()
{
    //�u�����f�B���O�X�e�[�g����
    D3D11_BLEND_DESC blendDesc;
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    for (int i = 0; i < 1; i++) {
        blendDesc.RenderTarget[i].BlendEnable = TRUE;
        blendDesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
        blendDesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        blendDesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
        blendDesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
        blendDesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
        blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    }
    m_Device->CreateBlendState(&blendDesc, &m_BlendState);
    float blendFactor[4] = { D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO, D3D11_BLEND_ZERO };
    m_Context->OMSetBlendState(m_BlendState, blendFactor, 0xffffffff);
}

void Renderer::createRasterizerState()
{
    D3D11_RASTERIZER_DESC rasterizerDesc;
    rasterizerDesc.FrontCounterClockwise = TRUE;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0;
    rasterizerDesc.DepthClipEnable = TRUE;
    rasterizerDesc.ScissorEnable = FALSE;
    rasterizerDesc.MultisampleEnable = FALSE;
    rasterizerDesc.AntialiasedLineEnable = FALSE;
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    m_Device->CreateRasterizerState(&rasterizerDesc, &m_RasterizerStateCullNone);
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    m_Device->CreateRasterizerState(&rasterizerDesc, &m_RasterizerStateCullBack);
    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    m_Device->CreateRasterizerState(&rasterizerDesc, &m_RasterizerStateWire);
    m_Context->RSSetState(m_RasterizerStateCullBack);
}

void Renderer::createSamplerState()
{
    HRESULT hr;
    //�T���v���[�X�e�[�gClamp�����`�ݒ�
    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = m_Device->CreateSamplerState(&samplerDesc, &m_SamplerStateClamp);
    WARNING(FAILED(hr), "Error", "�e�N�X�`���T���v���[Clamp�������ł��܂���");
    m_Context->PSSetSamplers(0, 1, &m_SamplerStateClamp);
    //�T���v���[�X�e�[�gWrap�����̂�
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    hr = m_Device->CreateSamplerState(&samplerDesc, &m_SamplerStateWrap);
    WARNING(FAILED(hr), "Error", "�e�N�X�`���T���v���[Wrap�������ł��܂���");
}

void Renderer::createShaderFromRes()
{
}

void Renderer::createConstantBuffer()
{
}

void Renderer::createTexCoordBuffer()
{
}

bool Renderer::CompileShader(const WCHAR* vsPath, const WCHAR* psPath, Shader& outShader)
{
    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* errBlob = nullptr;
    auto pDevice = GetDevice();

    // �V�F�[�_�[�R���p�C��
    auto hr = D3DCompileFromFile(
        vsPath,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "vs_4_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        &vsBlob,
        &errBlob
    );
    WARNING(FAILED(hr), "Error", "���_�V�F�[�_�[�̃R���p�C���Ɏ��s���܂���");

    // ���_�V�F�[�_�쐬(�V�F�[�_�I�u�W�F�N�g�쐬)
    ID3D11VertexShader* pVertexShader = nullptr;
    hr = pDevice->CreateVertexShader(
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        nullptr,
        &pVertexShader
    );
    WARNING(FAILED(hr), "Error", "���_�V�F�[�_�[�̍쐬�Ɏ��s���܂���");

    // ���̓��C�A�E�g�I�u�W�F�N�g�쐬
    ID3D11InputLayout* pInputLayout = nullptr;
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    hr = pDevice->CreateInputLayout(
        layout,
        _countof(layout),
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        &pInputLayout
    );
    WARNING(FAILED(hr), "Error", "���̓��C�A�E�g�̍쐬�Ɏ��s���܂���");

    // �s�N�Z���V�F�[�_�[�쐬
    ID3DBlob* psBlob = nullptr;
    hr = D3DCompileFromFile(
        psPath,
        nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE,
        "main",
        "ps_4_0",
        D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        &psBlob,
        &errBlob
    );

    ID3D11PixelShader* pPixelShader = nullptr;
    hr = pDevice->CreatePixelShader(
        psBlob->GetBufferPointer(),
        psBlob->GetBufferSize(),
        nullptr,
        &pPixelShader
    );
    WARNING(FAILED(hr), "Error", "�s�N�Z���V�F�[�_�[�̍쐬�Ɏ��s���܂���");

    outShader.pVertexShader = pVertexShader;
    outShader.pPixelShader = pPixelShader;
    outShader.pInputLayout = pInputLayout;

    return true;
}

Renderer::~Renderer()
{
}
