#pragma once
#include <d3d11.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")

#include <string>
#include <vector>
#include <map>

// �V�F�[�_�[�̊�{�N���X
class Shader
{
protected:
	// �V�F�[�_�[�̎��
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
	/// �V�F�[�_�[�t�@�C����ǂݍ���
	/// </summary>
	/// <param name="pFileName"></param>
	/// <returns></returns>
	HRESULT Load(const char* pFileName);
	/// <summary>
	/// �����񂩂�V�F�[�_���R���p�C��
	/// </summary>
	/// <param name="pCode"></param>
	/// <returns></returns>
	HRESULT Compile(const char* pCode);
	// �V�F�[�_�[���쐬
	void WriteBuffer(UINT slot, void* pData);

	// �e�N�X�`���̐ݒ�
//	void SetTexture(UINT slot, Texture* pTexture);
// 
	// �V�F�[�_�[��`��Ɏg�p
	virtual void Bind(void) = 0;
private:
	HRESULT Make(void* pData, UINT size);
protected:
	/// <summary>
	/// �V�F�[�_�[�t�@�C����ǂݍ��񂾂��ƁA�V�F�[�_�[�̎�ނɉ����ď������s��
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
// ���_�V�F�[�_�[
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
// �s�N�Z���V�F�[�_�[
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