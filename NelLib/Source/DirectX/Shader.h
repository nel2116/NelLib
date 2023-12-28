#pragma once
#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#include <string>
#include <vector>
#include <map>

// シェーダーの基本クラス
class Shader
{
protected:
	// シェーダーの種類
	enum ShaderType
	{
		Vertex,
		Pixel,
	};
protected:
	Shader(ShaderType type);
public:
	virtual ~Shader();

public:
	/// <summary>
	/// シェーダーファイルを読み込む
	/// </summary>
	/// <param name="pFileName"></param>
	/// <returns></returns>
	HRESULT Load(const char* pFileName);
	/// <summary>
	/// 文字列からシェーダをコンパイル
	/// </summary>
	/// <param name="pCode"></param>
	/// <returns></returns>
	HRESULT Compile(const char* pCode);
	// シェーダーを作成
	void WriteBuffer(UINT slot, void* pData);

	// テクスチャの設定
//	void SetTexture(UINT slot, Texture* pTexture);
// 
	// シェーダーを描画に使用
	virtual void Bind(void) = 0;
private:
	HRESULT Make(void* pData, UINT size);
protected:
	/// <summary>
	/// シェーダーファイルを読み込んだあと、シェーダーの種類に応じて処理を行う
	/// </summary>
	/// <param name="pData"></param>
	/// <param name="size"></param>
	/// <returns></returns>
	virtual HRESULT MakeShader(void* pData,UINT size) = 0;
private:
	ShaderType m_type;
protected:
	std::vector<ID3D11Buffer*> m_Buffers;
	std::vector<ID3D11ShaderResourceView*> m_Textures;
};

// -----------------
// 頂点シェーダー
class VertexShader : public Shader
{
public:
	VertexShader();
	~VertexShader();
 void Bind(void) override;
protected:
HRESULT MakeShader(void* pData, UINT size) override;
private:
	ID3D11VertexShader* m_pVS;
	ID3D11InputLayout* m_pInputLayout;
};

// -----------------
// ピクセルシェーダー
class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader();
	void Bind(void) override;
protected:
HRESULT MakeShader(void* pData, UINT size) override;
private:
	ID3D11PixelShader* m_pPS;
};