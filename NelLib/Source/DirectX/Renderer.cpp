#include <d3dcompiler.h>
#pragma comment(lib,"d3dcompiler.lib")
#include "Renderer.h"
#include "../System/window.h"

void Renderer::Init(int baseWidth, int baseHeight)
{
    //基準となる幅と高さ
    if (baseWidth == 0 || baseHeight == 0) {
        m_Width = (float)ClientWidth;
        m_Height = (float)ClientHeight;
    }
    else {
        m_Width = (float)baseWidth;
        m_Height = (float)baseHeight;
    }

    createDevice();             // デバイスの生成
    createRenderTarget();       // レンダーターゲットの生成
    setViewport();              // ビューポートの設定

    createDepthStencielState(); // 深度ステンシルステートの生成
    createBlendState();         // ブレンドステートの生成
    createRasterizerState();    // ラスタライザーステートの生成
    createSamplerState();       // サンプラーステートの生成

//    createShaderFromRes();      // シェーダーの生成
//    createConstantBuffer();     // 定数バッファの生成

//    createTexCoordBuffer();     // テクスチャ座標バッファの生成
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
    // デバイスの解放
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
    // レンダーターゲットのクリア
	m_Context->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	// 深度ステンシルのクリア
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
// バックバッファをフロントバッファに反映
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
    //マルチサンプリング対応
    //デバイスの生成
    HRESULT hr;
    hr = D3D11CreateDevice(
        NULL,                       // デフォルトアダプターを使用
        D3D_DRIVER_TYPE_HARDWARE,   // ハードウェアアクセラレータを使用
        NULL,   		            // ソフトウェアラスタライザを使用
        0,  					    // フラグ
        NULL,   			        // デフォルトのフィーチャーレベル配列を使用
        0,  				        // デフォルトのフィーチャーレベル配列のサイズ
        D3D11_SDK_VERSION,          // SDKバージョン
        &m_Device,                  // デバイス
        NULL,                       // サポートされているフィーチャーレベル
        &m_Context);                // デバイスコンテキスト
    WARNING(FAILED(hr), "D3D11CreateDevice", "");
    //使用可能なMSAAを取得
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
    //インターフェース取得
    IDXGIDevice1* hpDXGI = NULL;
    hr = m_Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&hpDXGI);
    WARNING(FAILED(hr), "QueryInterface", "");
    //アダプター取得
    IDXGIAdapter* hpAdapter = NULL;
    hr = hpDXGI->GetAdapter(&hpAdapter);
    WARNING(FAILED(hr), "GetAdapter", "");
    //ファクトリー取得
    IDXGIFactory* hpDXGIFactory = NULL;
    hr = hpAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&hpDXGIFactory);
    WARNING(FAILED(hr), "GetParent", "");
    //スワップチェイン作成
    DXGI_SWAP_CHAIN_DESC hDXGISwapChainDesc;
    hDXGISwapChainDesc.BufferCount = 1;                                                     // バックバッファの数
    hDXGISwapChainDesc.BufferDesc.Width = ClientWidth;                                      // バックバッファの幅
    hDXGISwapChainDesc.BufferDesc.Height = ClientHeight;                                    // バックバッファの高さ
    hDXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                      // フォーマット
    hDXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;                               // リフレッシュレート
    hDXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;		                        // リフレッシュレート
    hDXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;  // スキャンラインオーダー
    hDXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;				    // スケーリング
    hDXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                       // バックバッファの使用法
    hDXGISwapChainDesc.OutputWindow = FindWindow("GameWindow", NULL);                       // 出力先のウィンドウハンドル
    hDXGISwapChainDesc.Windowed = TRUE;								                        // ウィンドウモード
    hDXGISwapChainDesc.SampleDesc = MSAA;								                    // マルチサンプリング
    hDXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;			                    // スワップエフェクト
    hDXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                      // フラグ
#ifndef _DEBUG//リリースモードの時
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
    //マルチサンプリング対応
// Create a render target view
    ID3D11Texture2D* backBuffer = NULL; // バックバッファ
    // バックバッファを取得
    HRESULT hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
    WARNING(FAILED(hr), "can't Get BackBuffer", "");
    // レンダーターゲットビューを作成
    hr = m_Device->CreateRenderTargetView(backBuffer, NULL, &m_RenderTargetView);
    backBuffer->Release();
    WARNING(FAILED(hr), "can't Create RenderTargetView", "");

    // Create a depth stencil texture
    D3D11_TEXTURE2D_DESC depthStencilTextureDesc;                           
    ZeroMemory(&depthStencilTextureDesc, sizeof(depthStencilTextureDesc));  // 構造体の初期化
    depthStencilTextureDesc.Width = ClientWidth;                            // 幅
    depthStencilTextureDesc.Height = ClientHeight;  				        // 高さ
    depthStencilTextureDesc.MipLevels = 1;                                  // ミップマップ数
    depthStencilTextureDesc.ArraySize = 1;                                  // 配列サイズ
    depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;         // フォーマット
    depthStencilTextureDesc.SampleDesc = MSAA;                              // マルチサンプリング
    depthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;                    // 使用法
    depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;           // バインドフラグ
    depthStencilTextureDesc.CPUAccessFlags = 0; 			                // CPUアクセスフラグ
    depthStencilTextureDesc.MiscFlags = 0; 				                    // ミスフラグ
    ID3D11Texture2D* depthStencilTexture = 0;                               // 深度ステンシルテクスチャ
    hr = m_Device->CreateTexture2D(&depthStencilTextureDesc, NULL, &depthStencilTexture);
    WARNING(FAILED(hr), "can't Create depth stencil texture", "");

    // Create a depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;                 
    ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));        // 構造体の初期化
    depthStencilViewDesc.Format = depthStencilTextureDesc.Format;           // フォーマット
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;   // ビューの次元
    depthStencilViewDesc.Texture2D.MipSlice = 0;    	                    // ミップスライス
    hr = m_Device->CreateDepthStencilView(depthStencilTexture, &depthStencilViewDesc, &m_DepthStencilView);
    WARNING(FAILED(hr), "can't Create DepthStencilView", "");
    SAFE_RELEASE(depthStencilTexture);

    // Set RenderTarget
    m_Context->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
}

void Renderer::setViewport()
{
    D3D11_VIEWPORT vp;
    float aspect = m_Width / m_Height;      // アスペクト比
    if ((float)ClientWidth / ClientHeight >= aspect) {
        float width = ClientHeight * aspect;        // 横幅
        float left = (ClientWidth - width) / 2.0f;  // 左端
        vp.Width = width;                           // 横幅
        vp.Height = (float)ClientHeight;            // 縦幅
        vp.MinDepth = 0.0f;                         // 最小深度
        vp.MaxDepth = 1.0f;                         // 最大深度
        vp.TopLeftX = left; 			            // 左端
        vp.TopLeftY = 0;                            // 上端
        m_Context->RSSetViewports(1, &vp);
    }
    else {
        float height = ClientWidth / aspect;        // 縦幅
        float top = (ClientHeight - height) / 2.0f; // 上端
        vp.Width = (float)ClientWidth;              // 横幅
        vp.Height = height;     	                // 縦幅  
        vp.MinDepth = 0.0f;                         // 最小深度
        vp.MaxDepth = 1.0f; 					    // 最大深度
        vp.TopLeftX = 0;    			            // 左端
        vp.TopLeftY = top;  			            // 上端
        m_Context->RSSetViewports(1, &vp);  
    }
}

void Renderer::createDepthStencielState()
{
    // Create depth stencil state
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    depthStencilDesc.DepthEnable = TRUE;                            // 深度テストを有効にする
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // 深度書き込みマスク
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;       // 深度比較関数
    depthStencilDesc.StencilEnable = FALSE;						    // ステンシルテストを有効にする
    HRESULT hr = m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);    
    WARNING(FAILED(hr), "Error", "");
    m_Context->OMSetDepthStencilState(m_DepthStencilState, 0);
}

void Renderer::createBlendState()
{
    //ブレンディングステート生成
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
    //サンプラーステートClamp生成～設定
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
    WARNING(FAILED(hr), "Error", "テクスチャサンプラーClampが生成できません");
    m_Context->PSSetSamplers(0, 1, &m_SamplerStateClamp);
    //サンプラーステートWrap生成のみ
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    hr = m_Device->CreateSamplerState(&samplerDesc, &m_SamplerStateWrap);
    WARNING(FAILED(hr), "Error", "テクスチャサンプラーWrapが生成できません");
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

    // シェーダーコンパイル
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
    WARNING(FAILED(hr), "Error", "頂点シェーダーのコンパイルに失敗しました");

    // 頂点シェーダ作成(シェーダオブジェクト作成)
    ID3D11VertexShader* pVertexShader = nullptr;
    hr = pDevice->CreateVertexShader(
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        nullptr,
        &pVertexShader
    );
    WARNING(FAILED(hr), "Error", "頂点シェーダーの作成に失敗しました");

    // 入力レイアウトオブジェクト作成
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
    WARNING(FAILED(hr), "Error", "入力レイアウトの作成に失敗しました");

    // ピクセルシェーダー作成
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
    WARNING(FAILED(hr), "Error", "ピクセルシェーダーの作成に失敗しました");

    outShader.pVertexShader = pVertexShader;
    outShader.pPixelShader = pPixelShader;
    outShader.pInputLayout = pInputLayout;

    return true;
}

Renderer::~Renderer()
{
}
