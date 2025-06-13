#include "Scene/GameObject.h"

namespace Ethereal
{
	uint64_t GameObject::s_NextID = 1; // Initialize static member

	GameObject::GameObject(const std::string& name)
		: m_ID(s_NextID++), m_Name(name)
	{
	}

	uint64_t GameObject::GetID() const
	{
		return m_ID;
	}
	const std::string& GameObject::GetName() const
	{
		return m_Name;
	}

	void GameObject::SetName(const std::string& name)
	{
		m_Name = name;
	}

	void GameObject::SetModel(std::shared_ptr<ModelAsset> model)
	{
		m_Model = model;
	}

	std::shared_ptr<ModelAsset> GameObject::GetModel() const
	{
		return m_Model;
	}

	Transform& GameObject::GetTransform()
	{
		return m_Transform;
	}

	const Transform& GameObject::GetTransform() const
	{
		return m_Transform;
	}

	// Convenience Transform API
	void GameObject::SetPosition(const DirectX::XMFLOAT3& position)
	{
		m_Transform.SetPosition(position);
	}

	void GameObject::SetRotation(const DirectX::XMFLOAT3& rotation)
	{
		m_Transform.SetRotation(rotation);
	}

	void GameObject::SetScale(const DirectX::XMFLOAT3& scale)
	{
		m_Transform.SetScale(scale);
	}

	const DirectX::XMFLOAT3& GameObject::GetPosition() const
	{
		return m_Transform.GetPosition();
	}

	const DirectX::XMFLOAT3& GameObject::GetRotation() const
	{
		return m_Transform.GetRotation();
	}

	const DirectX::XMFLOAT3& GameObject::GetScale() const
	{
		return m_Transform.GetScale();
	}
}