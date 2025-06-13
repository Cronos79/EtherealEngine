#pragma once

#include "Assets/IAsset.h"
#include "Assets/Mesh.h"
#include <vector>
#include <string>
#include "EtherealEngine.h"

namespace Ethereal
{
	class ENGINE_API ModelAsset : public IAsset
	{
	public:
		bool LoadFromFile(const std::string& path);

		const std::vector<Mesh>& GetMeshes() const
		{
			return m_Meshes;
		}

	private:
		std::vector<Mesh> m_Meshes;
	};
}