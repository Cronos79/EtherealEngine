#pragma once
#include "Assets/IAsset.h"
#include <d3d11.h>
#include <wrl/client.h>
#include <string>

namespace Ethereal
{
	class ShaderAsset : public IAsset
	{
	public:
		enum class ShaderType {
			Vertex, Pixel, Geometry, Unknown
		};

		ShaderAsset(ShaderType type);
		bool LoadFromFile(ID3D11Device* device, const std::string& path);
		ShaderType InferShaderType(const std::string& name);
		bool CreateInputLayout(ID3D11Device* device, const D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutCount);

		ShaderType GetType() const
		{
			return m_Type;
		}

		ID3D11VertexShader* GetVertexShader() const
		{
			return m_VertexShader.Get();
		}
		ID3D11PixelShader* GetPixelShader()  const
		{
			return m_PixelShader.Get();
		}
		ID3D11GeometryShader* GetGeometryShader() const
		{
			return m_GeometryShader.Get();
		}
		ID3DBlob* GetBytecode() const
		{
			return m_ShaderBlob.Get();
		}
		ID3D11InputLayout* GetInputLayout() const
		{
			return m_InputLayout.Get();
		}

	private:
		ShaderType m_Type = ShaderType::Unknown;
		Microsoft::WRL::ComPtr<ID3DBlob> m_ShaderBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	};
}