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
}