#pragma once
// ====== インクルード部 ======
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
	/// <param name="fullscreen">フルスクリーンかどうか</param>
	/// <remarks>ライブラリ側で呼んでいるので呼ぶ必要なし</remarks>
	void Init(int baseWidth, int baseHeight,bool fullscreen);
	/// <summary>
	/// 解放関数
	/// </summary>
	/// <remarks>解放を行う</remarks>
	/// <remarks>ライブラリ側で呼んでいるので呼ぶ必要なし</remarks>
	void Release();
	void Begin();
	void End();
	void SetClearColor(float r, float g, float b, float a);

	/// <summary>
	/// デバイスの取得関数
	/// </summary>
	/// <returns>デバイス</returns>
	/// <remarks>デバイスを取得する</remarks>
	ID3D11Device* GetDevice() { return m_pDevice; }

	/// <summary>
	/// デバイスコンテキストの取得関数
	/// </summary>
	/// <returns>デバイスコンテキスト</returns>
	/// <remarks>デバイスコンテキストを取得する</remarks>
	ID3D11DeviceContext* GetContext() { return m_pContext; }

	/// <summary>
	/// スワップチェインの取得関数
	/// </summary>
	/// <returns>スワップチェイン</returns>
	/// <remarks>スワップチェインを取得する</remarks>
	IDXGISwapChain* GetSwapChain() { return m_pSwapChain; }

	/// <summary>
	/// レンダーターゲットビューの取得関数
	/// </summary>
	/// <returns>レンダーターゲットビュー</returns>
	/// <remarks>レンダーターゲットビューを取得する</remarks>
	RenderTarget* GetDefaultRTV(){ return m_pRTV; }

	/// <summary>
	/// 深度ステンシルビューの取得関数
	/// </summary>
	/// <returns>深度ステンシルビュー</returns>
	/// <remarks>深度ステンシルビューを取得する</remarks>
	DepthStencil* GetDefaultDSV(){ return m_pDSV; }

	/// <summary>
	/// レンダーターゲットの設定関数
	///	</summary>
	/// <param name="num">レンダーターゲットの数</param>
	/// <param name="ppViews">レンダーターゲットビュー</param>
	/// <param name="pView">深度ステンシルビュー</param>
	/// <remarks>レンダーターゲットを設定する</remarks>
	void SetRenderTargets(UINT num, RenderTarget** ppViews, DepthStencil* pView);

	/// <summary>
	/// カリングモードの設定関数
	/// </summary>
	/// <param name="cull">カリングモード</param>
	/// <remarks>カリングモードを設定する</remarks>
	void SetCullingMode(D3D11_CULL_MODE cull);

	/// <summary>
	/// ブレンドステートの設定関数
	///	</summary>
	/// <param name="blend">ブレンドモード</param>
	/// <remarks>ブレンドステートを設定する</remarks>
	void SetBlendMode(BlendMode blend);

	/// <summary>
	/// サンプラーステートの設定関数
	/// </summary>
	/// <param name="state">サンプラーステート</param>
	/// <remarks>サンプラーステートを設定する</remarks>
	void SetSamplerState(SamplerState state);

	float GetWidth() { return m_Width; }
	float GetHeight() { return m_Height; }

	void rect(float px, float py, float w, float h, float rad, float z);

private:	// ----- メンバ関数 -----
	void CreateRectBuffer();
	void CreateDefaultShader();

private:	// ----- メンバ変数 -----
	// DirectX11関連
	ID3D11Device* m_pDevice = nullptr;			            // デバイス
	ID3D11DeviceContext* m_pContext = nullptr;	            // デバイスコンテキスト
	IDXGISwapChain* m_pSwapChain = nullptr;		            // スワップチェイン
	DXGI_SAMPLE_DESC MSAA = { 0,0 };			            // MSAA設定
	RenderTarget* m_pRTV = nullptr;							// レンダーターゲットビュー
	DepthStencil* m_pDSV = nullptr;							// 深度ステンシルビュー
	ID3D11BlendState* m_pBlendState[BLEND_MAX];	            // ブレンドステート
	ID3D11RasterizerState* m_pRasterizerState[3];			// ラスタライザーステート
	ID3D11SamplerState* m_pSamplerState[SAMPLER_MAX];		// サンプラーステート
	float m_ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };		// クリアカラー
	float m_Width = 0.0f;									// 幅
	float m_Height = 0.0f;									// 高さ
	std::vector<MeshBuffer*> m_MeshBuffer;					// メッシュバッファ

	// 共通使用マトリックス
	MATRIX m_World;											// ワールド行列
	MATRIX m_Proj;											// 射影行列
	
	// デフォルト値
	COLOR m_FillColor;										// 塗りつぶし色

	// デフォルトシェーダ
	Shader* m_pVS;											// 頂点シェーダ
	Shader* m_pPS;											// ピクセルシェーダ

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