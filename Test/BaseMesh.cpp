#include "BaseMesh.h"

BaseMesh::BaseMesh()
{
	vertexCount = 0;
	indexCount = 0;
}

BaseMesh::~BaseMesh()
{
	if(indexBuffer)
	{
		indexBuffer->Release();
	}

	if(vertexBuffer)
	{
		vertexBuffer->Release();
	}
}

void BaseMesh::Render(ID3D11DeviceContext * context)
{
	UINT stride = sizeof(PNTVertex);
	UINT offset = 0;

	//Set vertex and index buffers.
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology.
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Draw
	context->DrawIndexed(indexCount, 0, 0);
}