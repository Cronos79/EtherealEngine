#pragma once

#include <string>
#include <vector>
#include <DirectXMath.h>
#include "Assets/Vertex.h"
#include <wrl/client.h>
#include <d3d11.h>
#include <stdint.h>

namespace Ethereal
{
	struct Mesh
	{
		std::string Name;
		std::vector<Vertex> Vertices;
		std::vector<uint32_t> Indices;
		uint32_t MaterialIndex = 0;
		DirectX::XMMATRIX Transform = DirectX::XMMatrixIdentity();

		// GPU buffers (created once during mesh loading)
		Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
		uint32_t IndexCount = 0;

		Mesh() = default;

		Mesh(const std::string& name,
			const std::vector<Vertex>& vertices,
			const std::vector<uint32_t>& indices,
			uint32_t materialIndex = 0,
			DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity())
			: Name(name),
			Vertices(vertices),
			Indices(indices),
			MaterialIndex(materialIndex),
			Transform(transform),
			IndexCount(static_cast<uint32_t>(indices.size()))
		{
		}

		void UploadToGPU(ID3D11Device* device)
		{
			if (!VertexBuffer && !Vertices.empty())
			{
				D3D11_BUFFER_DESC vbDesc = {};
				vbDesc.Usage = D3D11_USAGE_DEFAULT;
				vbDesc.ByteWidth = UINT(Vertices.size() * sizeof(Vertex));
				vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

				D3D11_SUBRESOURCE_DATA vbData = {};
				vbData.pSysMem = Vertices.data();

				device->CreateBuffer(&vbDesc, &vbData, VertexBuffer.GetAddressOf());
			}

			if (!IndexBuffer && !Indices.empty())
			{
				D3D11_BUFFER_DESC ibDesc = {};
				ibDesc.Usage = D3D11_USAGE_DEFAULT;
				ibDesc.ByteWidth = UINT(Indices.size() * sizeof(uint32_t));
				ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

				D3D11_SUBRESOURCE_DATA ibData = {};
				ibData.pSysMem = Indices.data();

				device->CreateBuffer(&ibDesc, &ibData, IndexBuffer.GetAddressOf());
			}
		}

		inline const std::vector<Vertex>& GetVertices() const
		{
			return Vertices;
		}
		inline const std::vector<uint32_t>& GetIndices() const
		{
			return Indices;
		}
	};
}
