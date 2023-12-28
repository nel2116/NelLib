#include "Vertex.h"
#include "Renderer.h"

Triangle::Triangle()
{
	vertices[0] = Vertex(0.0f, 0.5f, 0.0f);
	vertices[1] = Vertex(0.5f, -0.5f, 0.0f);
	vertices[2] = Vertex(-0.5f, -0.5f, 0.0f);
}

Triangle::~Triangle()
{
	SAFE_RELEASE(vertexBuffer)
}

bool Triangle::CreateVertexBuffer()
{
HRESULT hr;

	// Create vertex buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;

	hr = RENDERER.GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);
	WARNING(FAILED(hr), "頂点バッファの作成に失敗しました", "");

	return true;
}

void Triangle::Draw()
{
	uint32_t strides[1] = { sizeof(Vertex) };
	uint32_t offsets[1] = { 0 };
	RENDERER.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	RENDERER.GetContext()->IASetVertexBuffers(0, 1, &vertexBuffer, strides, offsets);
	RENDERER.GetContext()->Draw(VERTEX_NUM, 0);
}
