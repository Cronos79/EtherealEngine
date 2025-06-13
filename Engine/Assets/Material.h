#pragma once

#include <string>
#include <wrl/client.h>
#include <d3d11.h>
#include <DirectXMath.h>

#include "Assets/TextureAsset.h"


namespace Ethereal
{
	class AssetManager;

	class Material
	{
	public:
		Material();
		~Material() = default;

		// Setters
		void SetDiffuseTextureName(const std::string& name);
		void SetNormalTextureName(const std::string& name);
		void SetSpecularTextureName(const std::string& name);
		void SetMetallicTextureName(const std::string& name);
		void SetRoughnessTextureName(const std::string& name);
		void SetDiffuseColor(const DirectX::XMFLOAT3& color);

		// Runtime asset resolving
		bool ResolveTextures(AssetManager* assetManager, ID3D11Device* device);

		// Getters
		const std::string& GetDiffuseTextureName() const;
		ID3D11ShaderResourceView* GetDiffuseTexture() const;
		ID3D11ShaderResourceView* GetNormalTexture() const;
		ID3D11ShaderResourceView* GetSpecularTexture() const;
		ID3D11ShaderResourceView* GetMetallicTexture() const;
		ID3D11ShaderResourceView* GetRoughnessTexture() const;
		const DirectX::XMFLOAT3& GetDiffuseColor() const;

	private:
		std::string m_DiffuseTextureName;
		std::string m_NormalTextureName;
		std::string m_SpecularTextureName;
		std::string m_MetallicTextureName;
		std::string m_RoughnessTextureName;
		DirectX::XMFLOAT3 m_DiffuseColor;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_DiffuseTextureView;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_NormalTextureView;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SpecularTextureView;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_MetallicTextureView;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_RoughnessTextureView;
	};
}