#pragma once
#include <DirectXMath.h>

namespace Ethereal
{
	struct ObjectConstants
	{
		DirectX::XMMATRIX World;
	};

	struct CameraConstants
	{
		DirectX::XMMATRIX View;
		DirectX::XMMATRIX Projection;
	};
}