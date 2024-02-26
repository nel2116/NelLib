#include "Renderer.h"
#include "Texture.h"
#include "Shader.h"
#include "MeshBuffer.h"
#include <System/window.h>


void Renderer::Init(int baseWidth, int baseHeight, bool fullscreen)
{
	m_FillColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	//基準となる幅と高さ
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
	ZeroMemory(&sd, sizeof(sd));						    // ゼロクリア
	sd.BufferDesc.Width = m_Width;						    // バックバッファの幅
	sd.BufferDesc.Height = m_Height;					    // バックバッファの高さ
	sd.BufferDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;	// バックバッファフォーマット(R,G,B,A)
	sd.SampleDesc.Count = 1;							    // マルチサンプルの数
	sd.BufferDesc.RefreshRate.Numerator = 1000;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	    // バックバッファの使用方法
	sd.BufferCount = 1;									    // バックバッファの数
	sd.OutputWindow = FindWindow("GameWindow", NULL);;	    // 関連付けるウインドウ
	sd.Windowed = fullscreen ? FALSE : TRUE;				// ウインドウモード
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;				// バックバッファの交換方法
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// フルスクリーン切り替えの許可

	// ドライバの種類
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,	// GPUで描画
		D3D_DRIVER_TYPE_WARP,		// 高精度(低速
		D3D_DRIVER_TYPE_REFERENCE,	// CPUで描画
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);	// ドライバの数

	UINT createDeviceFlags = 0;

#ifndef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;	// デバッグレイヤーを有効にする
#endif // !_DEBUG



	// 機能レベル
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,		// DirectX11.1対応GPUレベル
		D3D_FEATURE_LEVEL_11_0,		// DirectX11対応GPUレベル
		D3D_FEATURE_LEVEL_10_1,		// DirectX10.1対応GPUレベル
		D3D_FEATURE_LEVEL_10_0,		// DirectX10対応GPUレベル
		D3D_FEATURE_LEVEL_9_3,		// DirectX9.3対応GPUレベル
		D3D_FEATURE_LEVEL_9_2,		// DirectX9.2対応GPUレベル
		D3D_FEATURE_LEVEL_9_1		// Direct9.1対応GPUレベル
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL,					// ディスプレイデバイスのアダプタ（NULLの場合最初に見つかったアダプタ）
			driverType,				// デバイスドライバのタイプ
			NULL,					// ソフトウェアラスタライザを使用する場合に指定する
			createDeviceFlags,		// デバイスフラグ
			featureLevels,			// 機能レベル
			numFeatureLevels,		// 機能レベル数
			D3D11_SDK_VERSION,		// 
			&sd,					// スワップチェインの設定
			&m_pSwapChain,			// IDXGIDwapChainインタフェース	
			&m_pDevice,				// ID3D11Deviceインタフェース
			&featureLevel,		// サポートされている機能レベル
			&m_pContext);		// デバイスコンテキスト
		if (SUCCEEDED(hr)) {
			break;
		}
	}
	WARNINGHR(hr, "DirectX11デバイスの作成に失敗しました");

	//--- レンダーターゲット設定
	m_pRTV = NEW RenderTarget();
	hr = m_pRTV->CreateFromScreen();
	WARNINGHR(hr, "レンダーターゲットの作成に失敗しました");
	m_pDSV = NEW DepthStencil();
	WARNINGHR(hr = m_pDSV->Create(m_pRTV->GetWidth(), m_pRTV->GetHeight(), false), "深度ステンシルの作成に失敗しました");
	SetRenderTargets(1, &m_pRTV, nullptr);


	//--- カリング設定
	D3D11_RASTERIZER_DESC rasterizer = {};
	D3D11_CULL_MODE cull[] = {
		D3D11_CULL_NONE,
		D3D11_CULL_FRONT,
		D3D11_CULL_BACK
	};
	rasterizer.FillMode = D3D11_FILL_SOLID;		// ポリゴンの塗りつぶし
	rasterizer.FrontCounterClockwise = false;	// 反時計回りが表面
	rasterizer.DepthBias = 0;					// 深度バイアス
	rasterizer.DepthBiasClamp = 0.0f;			// 深度バイアスのクランプ
	rasterizer.SlopeScaledDepthBias = 0.0f;		// スロープスケール付き深度バイアス
	rasterizer.DepthClipEnable = true;			// 深度クリッピングの有効
	rasterizer.ScissorEnable = false;			// シザー矩形の有効
	rasterizer.MultisampleEnable = false;		// マルチサンプリングの有効
	rasterizer.AntialiasedLineEnable = false;	// アンチエイリアス線の有効

	for (int i = 0; i < 3; ++i)
	{
		rasterizer.CullMode = cull[i];
		hr = m_pDevice->CreateRasterizerState(&rasterizer, &m_pRasterizerState[i]);
		WARNINGHR(hr, "ラスタライザーステートの作成に失敗しました");
	}
	SetCullingMode(D3D11_CULL_BACK);

	//--- 深度テスト


	//--- アルファブレンディング
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
		WARNINGHR(hr, "ブレンドステートの作成に失敗しました");
	}
	SetBlendMode(BLEND_ALPHA);

	// サンプラー
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
		WARNINGHR(hr, "サンプラーステートの作成に失敗しました");
	}
	SetSamplerState(SAMPLER_LINEAR);

	// クリアカラーの設定
//	SetClearColor(0.3f, 0.6f, 1.0f, 1.0f);
	SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::Release()
{
	// デバイスの解放
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
	// バックバッファとフロントバッファの入れ替え
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

	// ビューポートの設定
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
