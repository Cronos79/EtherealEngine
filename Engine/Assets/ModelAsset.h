#pragma once

#include "Assets/IAsset.h"
#include "Assets/Mesh.h"
#include <vector>
#include <string>
#include <memory>
#include "EtherealEngine.h"
#include "Assets/Material.h"

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
		const std::vector<std::shared_ptr<Material>>& GetMaterials() const
		{
			return m_Materials;
		}

	private:
		std::vector<Mesh> m_Meshes;
		std::vector<std::shared_ptr<Material>> m_Materials;
	};
}