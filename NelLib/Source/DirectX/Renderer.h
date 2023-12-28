#pragma once
// ====== インクルード部 ======
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

// ====== クラス宣言部 ======
class Renderer
{
public:		// ----- メンバ関数 -----
	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <remarks>初期化を行う</remarks>
	/// <param name="baseWidth">幅</param>
	/// <param name="baseHeight">高さ</param>
	/// <remarks>ライブラリ側で呼んでいるので呼ぶ必要なし</remarks>
	void Init(int baseWidth, int baseHeight);
	/// <summary>
	/// 解放関数
	/// </summary>
	/// <remarks>解放を行う</remarks>
	/// <remarks>ライブラリ側で呼んでいるので呼ぶ必要なし</remarks>
	void Release();
	void Begin();
	void End();
	void Present();
	void SetClearColor(float r, float g, float b, float a);

	/// <summary>
	/// デバイスの取得関数
	/// </summary>
	/// <returns>デバイス</returns>
	/// <remarks>デバイスを取得する</remarks>
	ID3D11Device* GetDevice() { return m_Device; }

	/// <summary>
	/// デバイスコンテキストの取得関数
	/// </summary>
	/// <returns>デバイスコンテキスト</returns>
	/// <remarks>デバイスコンテキストを取得する</remarks>
	ID3D11DeviceContext* GetContext() { return m_Context; }


private:	// ----- メンバ関数 -----
	/// <summary>
	/// デバイスの作成関数
	/// </summary>
	/// <remarks>デバイスの作成を行う</remarks>
	void createDevice();

	/// <summary>
	/// レンダーターゲットの作成関数
	/// </summary>
	/// <remarks>レンダーターゲットの作成を行う</remarks>
	void createRenderTarget();

	/// <summary>
	/// ビューポートの設定関数
	/// </summary>
	/// <remarks>ビューポートの設定を行う</remarks>
	void setViewport();

	/// <summary>
	/// 深度ステンシルステートの作成関数
	/// </summary>
	/// <remarks>深度ステンシルステートの作成を行う</remarks>
	void createDepthStencielState();

	/// <summary>
	/// ブレンドステートの作成関数
	/// </summary>
	/// <remarks>ブレンドステートの作成を行う</remarks>
	void createBlendState();

	/// <summary>
	/// ラスタライザーステートの作成関数
	/// </summary>
	/// <remarks>ラスタライザーステートの作成を行う</remarks>
	void createRasterizerState();

	/// <summary>
	/// サンプラーステートの作成関数
	/// </summary>
	/// <remarks>サンプラーステートの作成を行う</remarks>
	void createSamplerState();

	/// <summary>
	/// シェーダーの生成関数
	/// </summary>
	/// <remarks>シェーダーの生成を行う</remarks>
	void createShaderFromRes();

	/// <summary>
	/// 定数バッファの生成関数
	/// </summary>
	/// <remarks>定数バッファの生成を行う</remarks>
	void createConstantBuffer();

	void createTexCoordBuffer();     // テクスチャ座標バッファの生成


	bool CompileShader(const WCHAR* vsPath, const WCHAR* psPath, Shader& outShader);

private:	// ----- メンバ変数 -----
	ID3D11Device* m_Device = nullptr;			            // デバイス
	ID3D11DeviceContext* m_Context = nullptr;	            // デバイスコンテキスト
	IDXGISwapChain* m_SwapChain = nullptr;		            // スワップチェイン
	DXGI_SAMPLE_DESC MSAA = { 0,0 };			            // MSAA設定
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;	// レンダーターゲットビュー
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;	// 深度ステンシルビュー
	ID3D11DepthStencilState* m_DepthStencilState = nullptr;	// 深度ステンシルステート
	ID3D11BlendState* m_BlendState = nullptr;	            // ブレンドステート
	ID3D11RasterizerState* m_RasterizerStateWire = 0;		// ラスタライザーステート
	ID3D11RasterizerState* m_RasterizerStateCullBack = 0;	// ラスタライザーステート
	ID3D11RasterizerState* m_RasterizerStateCullNone = 0;	// ラスタライザーステート
	ID3D11SamplerState* m_SamplerStateClamp = 0;			// サンプラーステート	
	ID3D11SamplerState* m_SamplerStateWrap = 0;				// サンプラーステート
	Triangle m_testTriangle;									// 三角形
	// ID3D11VertexShader* m_VertexShader = nullptr;			// 頂点シェーダー
	// ID3D11PixelShader* m_PixelShader = nullptr;				// ピクセルシェーダー
	// ID3D11InputLayout* m_VertexLayout = nullptr;				// 頂点レイアウト
	// ID3D11Buffer* m_ConstantBuffer = nullptr;				// 定数バッファ
	float m_ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };		// クリアカラー
	// VertexShader* m_pVS;									// 頂点シェーダー
	// PixelShader* m_pPS;										// ピクセルシェーダー
	Shader m_testShader;

	float m_Width = 0.0f;									// 幅
	float m_Height = 0.0f;									// 高さ

public:		// 以下シングルトン関連
	~Renderer();
	/// <summary>
	/// レンダラーのインスタンスを取得する関数
	/// </summary>
	/// <returns>レンダラーのインスタンス</returns>
	/// <remarks>この関数を呼ぶと、レンダラーのインスタンスが取得できる</remarks>
	static Renderer& GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Renderer();
		}
		return *m_instance;
	}

	/// <summary>
	/// レンダラーのインスタンスを破棄する関数
	/// </summary>
	static void DestroyInstance()
	{
		SAFE_DELETE(m_instance);
	}

private:
	// 唯一のインスタンス用ポインタ
	static inline Renderer* m_instance = nullptr;
	Renderer() {}
};

#define RENDERER Renderer::GetInstance()