#pragma once
#include "Assets/IAsset.h"
#include <wrl/client.h>
#include <d3d11.h>
#include <string>
#include <DirectXMath.h>
#include <WICTextureLoader.h>

namespace Ethereal
{
	class TextureAsset : public IAsset
	{
	public:
		TextureAsset() = default;
		~TextureAsset() = default;

		bool LoadFromFile(ID3D11Device* device, const std::string& path);

		ID3D11ShaderResourceView* GetTextureView() const
		{
			return m_TextureView.Get();
		}

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TextureView;
		std::string m_SourcePath;
	};
}