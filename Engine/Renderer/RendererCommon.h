#pragma once

#include <DirectXMath.h>

namespace Ethereal
{
	class Mesh;
	class Material;

	struct Renderable
	{
		const Mesh* mesh = nullptr;
		const Material* material = nullptr;
		DirectX::XMMATRIX worldMatrix;
	};
}