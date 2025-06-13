#pragma once

#include "Core/Transform.h"
#include "Assets/ModelAsset.h"
#include <memory>
#include <string>
#include "EtherealEngine.h"

namespace Ethereal
{
	class ENGINE_API GameObject
	{
	public:
		GameObject(const std::string& name);
		~GameObject() = default;

		// Identity
		uint64_t GetID() const;
		const std::string& GetName() const;
		void SetName(const std::string& name);

		// Model
		void SetModel(std::shared_ptr<ModelAsset> model);
		std::shared_ptr<ModelAsset> GetModel() const;

		// Transform Access
		Transform& GetTransform();
		const Transform& GetTransform() const;

		// Convenience Transform Manipulation
		void SetPosition(const DirectX::XMFLOAT3& position);
		void SetRotation(const DirectX::XMFLOAT3& rotation); // Euler angles
		void SetScale(const DirectX::XMFLOAT3& scale);

		const DirectX::XMFLOAT3& GetPosition() const;
		const DirectX::XMFLOAT3& GetRotation() const;
		const DirectX::XMFLOAT3& GetScale() const;

	private:
		uint64_t m_ID;
		std::string m_Name;
		Transform m_Transform;
		std::shared_ptr<ModelAsset> m_Model;

		static uint64_t s_NextID;
	};
}