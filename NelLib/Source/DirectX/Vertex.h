#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
namespace DX = DirectX;

struct Vertex
{
	DX::XMFLOAT3 position;
	DX::XMFLOAT3 normal;
	DX::XMFLOAT2 texCoord;
	DX::XMFLOAT3 tangent;
	DX::XMFLOAT3 bitangent;

	Vertex() {}
	Vertex(float x, float y, float z)
	{
		position = DX::XMFLOAT3(x, y, z);
		normal = DX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		texCoord = DX::XMFLOAT2(0.0f, 0.0f);
		tangent = DX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		bitangent = DX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	Vertex(float x, float y, float z, float u, float v)
	{
		position = DX::XMFLOAT3(x, y, z);
		normal = DX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		texCoord = DX::XMFLOAT2(u, v);
		tangent = DX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		bitangent = DX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz)
	{
		position = DX::XMFLOAT3(x, y, z);
		normal = DX::XMFLOAT3(nx, ny, nz);
		texCoord = DX::XMFLOAT2(u, v);
		tangent = DX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		bitangent = DX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz, float tx, float ty, float tz)
	{
		position = DX::XMFLOAT3(x, y, z);
		normal = DX::XMFLOAT3(nx, ny, nz);
		texCoord = DX::XMFLOAT2(u, v);
		tangent = DX::XMFLOAT3(tx, ty, tz);
		bitangent = DX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	Vertex(float x, float y, float z, float u, float v, float nx, float ny, float nz, float tx, float ty, float tz, float btx, float bty, float btz)
	{
		position = DX::XMFLOAT3(x, y, z);
		normal = DX::XMFLOAT3(nx, ny, nz);
		texCoord = DX::XMFLOAT2(u, v);
		tangent = DX::XMFLOAT3(tx, ty, tz);
		bitangent = DX::XMFLOAT3(btx, bty, btz);
	}
};

struct Triangle
{
	static constexpr size_t VERTEX_NUM = 3;
	Vertex vertices[VERTEX_NUM];
	ID3D11Buffer* vertexBuffer = nullptr;

	Triangle();
	~Triangle();
	bool CreateVertexBuffer();
	void Draw();
};