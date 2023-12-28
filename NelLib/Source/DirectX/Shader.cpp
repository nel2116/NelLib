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

	// �t�@�C����ǂݍ���
	FILE* fp;
	fopen_s(&fp, pFileName, "rb");
	if (!fp) { return hr; }

	// �t�@�C���̃T�C�Y�𒲂ׂ�
	int fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	// �������ɓǂݍ���
	fseek(fp, 0, SEEK_SET);
	char* pData = new char[fileSize];
	fread(pData, fileSize, 1, fp);	
	fclose(fp);

	// �V�F�[�_�쐬
	hr = Make(pData, fileSize);

	// �I������
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

	HRESULT hr = E_FAIL;		// �G���[�R�[�h
	ID3DBlob* pBlob = nullptr;	// �R���p�C����̃f�[�^
	ID3DBlob* error = nullptr;	// �G���[���
	UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;	// �R���p�C���t���O
	hr = D3DCompile(pCode, strlen(pCode), nullptr, nullptr, nullptr, "main", pTargetList[m_type], compileFlag, 0, &pBlob, &error);	// �R���p�C��
	WARNING(hr, "�V�F�[�_�R���p�C�����s", "");

	// �V�F�[�_�쐬
	hr = Make(pBlob->GetBufferPointer(), pBlob->GetBufferSize());

	// �I������
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

	// ��͗p�̃��t���N�V�����쐬
	ID3D11ShaderReflection* pReflection = nullptr;
	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
	if (FAILED(hr)) { return hr; }

	// �萔�o�b�t�@�쐬
	D3D11_SHADER_DESC shaderDesc;
	pReflection->GetDesc(&shaderDesc);
	m_Buffers.resize(shaderDesc.ConstantBuffers, nullptr);
	for (UINT i = 0; i < shaderDesc.ConstantBuffers; ++i)
	{
		// �V�F�[�_�[�̒萔�o�b�t�@�̏����擾
		D3D11_SHADER_BUFFER_DESC bufferDesc;
		ID3D11ShaderReflectionConstantBuffer* pConstBuffer = pReflection->GetConstantBufferByIndex(i);
		pConstBuffer->GetDesc(&bufferDesc);

		// �쐬����o�b�t�@�̏��
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = bufferDesc.Size;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		// �o�b�t�@�쐬
		hr = pDevice->CreateBuffer(&desc, nullptr, &m_Buffers[i]);
		if (FAILED(hr)) { return hr; }
	}
	// �e�N�X�`���̈�쐬
	m_Textures.resize(shaderDesc.BoundResources, nullptr);
	return MakeShader(pData, size);
}

// -----------------
// ���_�V�F�[�_�[
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

	// �V�F�[�_�[�쐬
	hr = pDevice->CreateVertexShader(pData, size, nullptr, &m_pVS);
	if (FAILED(hr)) { return hr; }

	// �V�F�[�_�쐬���ɃV�F�[�_���t���N�V������ʂ��ăC���v�b�g���C�A�E�g���擾
	// �Z�}���e�B�N�X�̔z�u�Ȃǂ��环�ʎq���쐬
	// ���ʎq���o�^�ρ��ė��p�A�Ȃ���ΐV�K�쐬
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
