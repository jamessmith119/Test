#include "BaseMesh.h"

BaseMesh::BaseMesh()
{
	vertexCount = 0;
	indexCount = 0;
}

BaseMesh::~BaseMesh()
{
	if(pixelShader)
	{
		pixelShader->Release();
		pixelShader = 0;
	}

	if(vertexShader)
	{
		vertexShader->Release();
		vertexShader = 0;
	}

	if(vertexLayout)
	{
		vertexLayout->Release();
		vertexLayout = 0;
	}

	if(indexBuffer)
	{
		indexBuffer->Release();
		indexBuffer = 0;
	}

	if(vertexBuffer)
	{
		vertexBuffer->Release();
		vertexBuffer = 0;
	}
}

//This is fine
void BaseMesh::Render(ID3D11DeviceContext * context)
{
	UINT stride = vertexBufferStride;
	UINT offset = 0;

	//Set vertex and index buffers.
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology.
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Draw
	context->DrawIndexed(indexCount, 0, 0);
}

ID3D11Buffer * BaseMesh::GetConstantBuffer()
{
	return constantBuffer;
}

ID3D11InputLayout * BaseMesh::GetVertexLayout()
{
	return vertexLayout;
}

ID3D11VertexShader * BaseMesh::GetVertexShader()
{
	return vertexShader;
}

ID3D11PixelShader * BaseMesh::GetPixelShader()
{
	return pixelShader;
}