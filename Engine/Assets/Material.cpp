#include "Assets/Material.h"
#include "Core/Logger.h"
#include "AssetManager.h"

namespace Ethereal
{
	Material::Material()
		: m_DiffuseColor(1.0f, 1.0f, 1.0f)
	{
	}

	void Material::SetDiffuseTextureName(const std::string& name)
	{
		m_DiffuseTextureName = name;
	}
	void Material::SetNormalTextureName(const std::string& name)
	{
		m_NormalTextureName = name;
	}
	void Material::SetSpecularTextureName(const std::string& name)
	{
		m_SpecularTextureName = name;
	}
	void Material::SetMetallicTextureName(const std::string& name)
	{
		m_MetallicTextureName = name;
	}
	void Material::SetRoughnessTextureName(const std::string& name)
	{
		m_RoughnessTextureName = name;
	}
	void Material::SetDiffuseColor(const DirectX::XMFLOAT3& color)
	{
		m_DiffuseColor = color;
	}

	bool Material::ResolveTextures(AssetManager* assetManager, ID3D11Device* device)
	{
		auto load = [&](const std::string& name, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& view) -> bool
			{
				if (name.empty()) return true;
				if (!assetManager->LoadTexture(name, device)) return false;
				auto tex = assetManager->Get<TextureAsset>(name);
				if (!tex) return false;
				view = tex->GetTextureView();
				return true;
			};

		return load(m_DiffuseTextureName, m_DiffuseTextureView) &&
			load(m_NormalTextureName, m_NormalTextureView) &&
			load(m_SpecularTextureName, m_SpecularTextureView) &&
			load(m_MetallicTextureName, m_MetallicTextureView) &&
			load(m_RoughnessTextureName, m_RoughnessTextureView);
	}

	const std::string& Material::GetDiffuseTextureName() const
	{
		return m_DiffuseTextureName;
	}
	ID3D11ShaderResourceView* Material::GetDiffuseTexture() const
	{
		return m_DiffuseTextureView.Get();
	}
	ID3D11ShaderResourceView* Material::GetNormalTexture() const
	{
		return m_NormalTextureView.Get();
	}
	ID3D11ShaderResourceView* Material::GetSpecularTexture() const
	{
		return m_SpecularTextureView.Get();
	}
	ID3D11ShaderResourceView* Material::GetMetallicTexture() const
	{
		return m_MetallicTextureView.Get();
	}
	ID3D11ShaderResourceView* Material::GetRoughnessTexture() const
	{
		return m_RoughnessTextureView.Get();
	}
	const DirectX::XMFLOAT3& Material::GetDiffuseColor() const
	{
		return m_DiffuseColor;
	}

	void Material::SetVertexShader(const std::string& shaderName)
	{
		m_VertexShaderName = shaderName;
	}

	const std::string& Material::GetVertexShaderName() const
	{
		return m_VertexShaderName;
	}

	void Material::SetPixelShader(const std::string& shaderName)
	{
		m_PixelShaderName = shaderName;
	}

	const std::string& Material::GetPixelShaderName() const
	{
		return m_PixelShaderName;
	}

	ID3D11PixelShader* Material::GetPixelShader() const
	{
		return m_PixelShader.Get();
	}

	Ethereal::ShaderAsset* Material::GetVertexShaderAsset() const
	{
		return m_VertexShaderAsset.get();
	}

	Ethereal::ShaderAsset* Material::GetPixelShaderAsset() const
	{
		return m_PixelShaderAsset.get();
	}

	ID3D11VertexShader* Material::GetVertexShader() const
	{
		return m_VertexShader.Get();
	}

	bool Material::ResolveShaders(AssetManager* assetManager, ID3D11Device* device)
	{
		bool success = true;

		// Vertex Shader
		if (!m_VertexShaderName.empty())
		{
			if (!assetManager->LoadShader(m_VertexShaderName, ShaderAsset::ShaderType::Vertex, device))
				success = false;
			else
			{
				auto shaderAsset = assetManager->Get<ShaderAsset>(m_VertexShaderName);
				if (shaderAsset && shaderAsset->GetType() == ShaderAsset::ShaderType::Vertex)
				{
					m_VertexShaderAsset = shaderAsset;
					m_VertexShader = shaderAsset->GetVertexShader();
				}
				else
					success = false;
			}
		}

		// Pixel Shader
		if (!m_PixelShaderName.empty())
		{
			if (!assetManager->LoadShader(m_PixelShaderName, ShaderAsset::ShaderType::Pixel, device))
				success = false;
			else
			{
				auto shaderAsset = assetManager->Get<ShaderAsset>(m_PixelShaderName);
				if (shaderAsset && shaderAsset->GetType() == ShaderAsset::ShaderType::Pixel)
				{
					m_PixelShaderAsset = shaderAsset;
					m_PixelShader = shaderAsset->GetPixelShader();
				}
				else
					success = false;
			}
		}

		return success;
	}
}