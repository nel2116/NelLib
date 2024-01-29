#pragma once
struct VERTEX_BUFFER
{
	struct ID3D11Buffer* obj;
	unsigned int numVertices;
	VERTEX_BUFFER() : obj(nullptr), numVertices(0) {}
	VERTEX_BUFFER(ID3D11Buffer* obj, unsigned int numVertices) : obj(obj), numVertices(numVertices) {}
};