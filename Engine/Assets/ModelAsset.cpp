#include "Assets/ModelAsset.h"
#include "Core/Logger.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Ethereal
{
	bool ModelAsset::LoadFromFile(const std::string& path)
	{
		m_Meshes.clear();

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(
			path,
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_ConvertToLeftHanded
		);

		if (!scene || !scene->HasMeshes())
		{
			EE_LOG_ERROR("Failed to load model: {}", path);
			return false;
		}

		m_Materials.clear();

		for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
		{
			const aiMaterial* aiMat = scene->mMaterials[i];
			auto material = std::make_shared<Material>();

			aiColor3D color(1.0f, 1.0f, 1.0f);
			if (AI_SUCCESS == aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, color))
			{
				const DirectX::XMFLOAT3 colorF3(color.r, color.g, color.b);
				material->SetDiffuseColor(colorF3);
			}

			if (aiMat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
			{
				aiString path;
				if (AI_SUCCESS == aiMat->GetTexture(aiTextureType_DIFFUSE, 0, &path))
				{
					//material->SetDiffuseTexturePath(path.C_Str());
					// You'll handle loading the texture in Material later
				}
			}

			m_Materials.push_back(material);
		}

		for (unsigned int m = 0; m < scene->mNumMeshes; ++m)
		{
			const aiMesh* assimpMesh = scene->mMeshes[m];
			Mesh mesh;
			mesh.Name = assimpMesh->mName.C_Str();
			mesh.MaterialIndex = assimpMesh->mMaterialIndex;

			mesh.Vertices.reserve(assimpMesh->mNumVertices);
			for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i)
			{
				Vertex vertex;
				memcpy(vertex.Position, &assimpMesh->mVertices[i], sizeof(float) * 3);
				memcpy(vertex.Normal, &assimpMesh->mNormals[i], sizeof(float) * 3);
				if (assimpMesh->HasTextureCoords(0))
				{
					vertex.TexCoord[0] = assimpMesh->mTextureCoords[0][i].x;
					vertex.TexCoord[1] = assimpMesh->mTextureCoords[0][i].y;
				}
				else
				{
					vertex.TexCoord[0] = 0.0f;
					vertex.TexCoord[1] = 0.0f;
				}
				mesh.Vertices.push_back(vertex);
			}

			for (unsigned int i = 0; i < assimpMesh->mNumFaces; ++i)
			{
				const aiFace& face = assimpMesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; ++j)
					mesh.Indices.push_back(face.mIndices[j]);
			}

			m_Meshes.push_back(mesh);

			EE_LOG_INFO("Loaded mesh '{}' with {} vertices, {} indices, material {}",
				mesh.Name, mesh.Vertices.size(), mesh.Indices.size(), mesh.MaterialIndex);
		}

		EE_LOG_INFO("Model '{}' loaded with {} mesh(es)", path, m_Meshes.size());
		return true;
	}
}