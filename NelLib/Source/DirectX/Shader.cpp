#pragma comment(lib,"d3dcompiler.lib")
#include <d3dcompiler.h>
#include "Shader.h"
#include "Renderer.h"

Shader::Shader(ShaderType type)
	: m_type(type)
{
}

Shader::~Shader()
{
	auto iter = m_Buffers.begin();
	while(iter != m_Buffers.end())
	{
		SAFE_RELEASE((*iter));
		++iter;
	}
}

HRESULT Shader::Load(const char* pFileName)
{
	HRESULT hr = E_FAIL;

	// ファイルを読み込む
	FILE* fp;
	fopen_s(&fp, pFileName, "rb");
	if (!fp) { return hr; }

	// ファイルのサイズを調べる
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// メモリに読み込み
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);	
	fclose(fp);

	// シェーダ作成
	hr = Make(pData, fileSize);

	// 終了処理
	SAFE_DELETE_ARRAY(pData);

	return hr;
}

HRESULT Shader::Compile(const char* pCode)
{
	static const char* pTargetList[] =
	{
		"vs_5_0",
		"ps_5_0",
	};

	HRESULT hr = E_FAIL;		// エラーコード
	ID3DBlob* pBlob = nullptr;	// コンパイル後のデータ
	ID3DBlob* error = nullptr;	// エラー情報
	UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;	// コンパイルフラグ
	hr = D3DCompile(pCode, strlen(pCode), nullptr, nullptr, nullptr, "main", pTargetList[m_type], compileFlag, 0, &pBlob, &error);	// コンパイル
	WARNING(hr, "シェーダコンパイル失敗", "");

	// シェーダ作成
	hr = Make(pBlob->GetBufferPointer(), pBlob->GetBufferSize());

	// 終了処理
	SAFE_RELEASE(pBlob);
	SAFE_RELEASE(error);
	return hr;
}

void Shader::WriteBuffer(UINT slot, void* pData)
{
	if (slot < m_Buffers.size())
		RENDERER.GetContext()->UpdateSubresource(m_Buffers[slot], 0, nullptr, pData, 0, 0);
}

HRESULT Shader::Make(void* pData, UINT size)
{
	HRESULT hr = E_FAIL;
	ID3D11Device* pDevice = RENDERER.GetDevice();

	// 解析用のリフレクション作成
	ID3D11ShaderReflection* pReflection = nullptr;
	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) { return hr; }

	// 定数バッファ作成
	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);
	m_Buffers.resize(shaderDesc.ConstantBuffers, nullptr);
	for (UINT i = 0; i < shaderDesc.ConstantBuffers; ++i)
	{
		// シェーダーの定数バッファの情報を取得
		D3D11_SHADER_BUFFER_DESC bufferDesc;
		ID3D11ShaderReflectionConstantBuffer* pConstBuffer = pReflection->GetConstantBufferByIndex(i);
		pConstBuffer->GetDesc(&bufferDesc);

		// 作成するバッファの情報
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = bufferDesc.Size;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		// バッファ作成
		hr = pDevice->CreateBuffer(&desc, nullptr, &m_Buffers[i]);
		if (FAILED(hr)) { return hr; }
	}
	// テクスチャ領域作成
	m_Textures.resize(shaderDesc.BoundResources, nullptr);
	return MakeShader(pData, size);
}

// -----------------
// 頂点シェーダー
VertexShader::VertexShader()
	: Shader(ShaderType::Vertex)
	, m_pVS(nullptr)
	, m_pInputLayout(nullptr)
{
}

VertexShader::~VertexShader()
{
	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pInputLayout);
}

void VertexShader::Bind(void)
{
	ID3D11DeviceContext* pContext = RENDERER.GetContext();
	pContext->VSSetShader(m_pVS, nullptr, 0);
	pContext->IASetInputLayout(m_pInputLayout);
	for (int i = 0; i < m_Buffers.size(); ++i)
	{
		pContext->VSSetConstantBuffers(i, 1, &m_Buffers[i]);
	}
	for (int i = 0; i < m_Textures.size(); ++i)
	{
		pContext->VSSetShaderResources(i, 1, &m_Textures[i]);
	}
}

HRESULT VertexShader::MakeShader(void* pData, UINT size)
{
	HRESULT hr = E_FAIL;
	ID3D11Device* pDevice = RENDERER.GetDevice();

	// シェーダー作成
	hr = pDevice->CreateVertexShader(pData, size, nullptr, &m_pVS);
	if (FAILED(hr)) { return hr; }

	// シェーダ作成時にシェーダリフレクションを通してインプットレイアウトを取得
	// セマンティクスの配置などから識別子を作成
	// 識別子が登録済→再利用、なければ新規作成
	ID3D11ShaderReflection* pReflection = nullptr;
	D3D11_SHADER_DESC shaderDesc;
	D3D11_INPUT_ELEMENT_DESC* pInputDesc = nullptr;
	D3D11_SIGNATURE_PARAMETER_DESC sigDesc;

	DXGI_FORMAT formats[][4] =
	{
		{
			DXGI_FORMAT_R32_UINT,
			DXGI_FORMAT_R32G32_UINT,
			DXGI_FORMAT_R32G32B32_UINT,
			DXGI_FORMAT_R32G32B32A32_UINT,
		}, {
			DXGI_FORMAT_R32_SINT,
			DXGI_FORMAT_R32G32_SINT,
			DXGI_FORMAT_R32G32B32_SINT,
			DXGI_FORMAT_R32G32B32A32_SINT,
		}, {
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_R32G32B32_FLOAT,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
		},
	};

	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) { return hr; }

	pReflection->GetDesc(&shaderDesc);
	pInputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];

	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		pReflection->GetInputParameterDesc(i, &sigDesc);
		pInputDesc[i].SemanticName = sigDesc.SemanticName;
		pInputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

		BYTE elementCount = sigDesc.Mask;
		elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
		elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);
		switch (sigDesc.ComponentType)
		{
		case D3D_REGISTER_COMPONENT_UINT32:
			pInputDesc[i].Format = formats[0][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_SINT32:
			pInputDesc[i].Format = formats[1][elementCount - 1];
			break;
		case D3D_REGISTER_COMPONENT_FLOAT32:
			pInputDesc[i].Format = formats[2][elementCount - 1];
			break;
		}
		pInputDesc[i].InputSlot = 0;
		pInputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		pInputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		pInputDesc[i].InstanceDataStepRate = 0;
	}

	hr = pDevice->CreateInputLayout(
		pInputDesc, shaderDesc.InputParameters,
		pData, size, &m_pInputLayout
	);

	delete[] pInputDesc;
	return hr;
}

PixelShader::PixelShader()
	: Shader(ShaderType::Pixel)
	, m_pPS(nullptr)
{
}

PixelShader::~PixelShader()
{
	SAFE_RELEASE(m_pPS);
}

void PixelShader::Bind(void)
{
ID3D11DeviceContext* pContext = RENDERER.GetContext();
	pContext->PSSetShader(m_pPS, nullptr, 0);
	for (int i = 0; i < m_Buffers.size(); ++i)
	{
		pContext->PSSetConstantBuffers(i, 1, &m_Buffers[i]);
	}
	for (int i = 0; i < m_Textures.size(); ++i)
	{
		pContext->PSSetShaderResources(i, 1, &m_Textures[i]);
	}
}

HRESULT PixelShader::MakeShader(void* pData, UINT size)
{
	return RENDERER.GetDevice()->CreatePixelShader(pData, size, nullptr, &m_pPS);
}
