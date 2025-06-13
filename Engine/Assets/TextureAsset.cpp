#include "Assets/TextureAsset.h"

namespace Ethereal
{
	bool TextureAsset::LoadFromFile(ID3D11Device* device, const std::string& path)
	{
		m_SourcePath = path;
		Microsoft::WRL::ComPtr<ID3D11Resource> resource;
		std::wstring widePath(path.begin(), path.end());

		HRESULT hr = DirectX::CreateWICTextureFromFile(
			device,
			widePath.c_str(),
			&resource,
			&m_TextureView
		);

		return SUCCEEDED(hr);
	}
}


