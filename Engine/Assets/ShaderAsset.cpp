#include "Assets/ShaderAsset.h"
#include "Core/Logger.h"
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

namespace Ethereal
{
	ShaderAsset::ShaderAsset(ShaderType type)
		: m_Type(type)
	{
	}

	bool ShaderAsset::LoadFromFile(ID3D11Device* device, const std::string& path)
	{
		HRESULT hr = D3DReadFileToBlob(std::wstring(path.begin(), path.end()).c_str(), &m_ShaderBlob);
		if (FAILED(hr))
		{
			EE_LOG_ERROR("Failed to read shader blob from file: {}", path);
			return false;
		}

		switch (m_Type)
		{
		case ShaderType::Vertex:
			hr = device->CreateVertexShader(m_ShaderBlob->GetBufferPointer(), m_ShaderBlob->GetBufferSize(), nullptr, &m_VertexShader);
			break;
		case ShaderType::Pixel:
			hr = device->CreatePixelShader(m_ShaderBlob->GetBufferPointer(), m_ShaderBlob->GetBufferSize(), nullptr, &m_PixelShader);
			break;
		case ShaderType::Geometry:
			hr = device->CreateGeometryShader(m_ShaderBlob->GetBufferPointer(), m_ShaderBlob->GetBufferSize(), nullptr, &m_GeometryShader);
			break;
		default:
			EE_LOG_ERROR("Unsupported shader type for: {}", path);
			return false;
		}

		if (FAILED(hr))
		{
			EE_LOG_ERROR("Failed to create shader from blob: {}", path);
			return false;
		}

		if (m_Type == ShaderType::Vertex)
		{
			// Example layout for a simple Vertex structure
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			if (!CreateInputLayout(device, layout, ARRAYSIZE(layout)))
			{
				EE_LOG_ERROR("Failed to create input layout for vertex shader");
				return false;
			}
		}

		EE_LOG_INFO("Shader loaded successfully: {}", path);
		return true;
	}

	Ethereal::ShaderAsset::ShaderType ShaderAsset::InferShaderType(const std::string& name)
	{
		if (name.ends_with("VS.cso")) return ShaderAsset::ShaderType::Vertex;
		if (name.ends_with("PS.cso")) return ShaderAsset::ShaderType::Pixel;
		if (name.ends_with("GS.cso")) return ShaderAsset::ShaderType::Geometry;
		return ShaderAsset::ShaderType::Unknown;
	}

	bool ShaderAsset::CreateInputLayout(ID3D11Device* device, const D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutCount)
	{
		if (m_Type != ShaderType::Vertex || !m_ShaderBlob)
		{
			EE_LOG_ERROR("Cannot create input layout: Shader is not a vertex shader or blob missing");
			return false;
		}

		HRESULT hr = device->CreateInputLayout(
			layout,
			layoutCount,
			m_ShaderBlob->GetBufferPointer(),
			m_ShaderBlob->GetBufferSize(),
			&m_InputLayout
		);

		if (FAILED(hr))
		{
			EE_LOG_ERROR("Failed to create input layout");
			return false;
		}

		return true;
	}

}