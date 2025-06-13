#include "Transform.h"

using namespace DirectX;

namespace Ethereal
{
	Transform::Transform()
		: m_Position(0.0f, 0.0f, 0.0f),
		m_Rotation(0.0f, 0.0f, 0.0f),
		m_Scale(1.0f, 1.0f, 1.0f)
	{
	}

	void Transform::SetPosition(const XMFLOAT3& position)
	{
		m_Position = position;
	}
	void Transform::SetRotation(const XMFLOAT3& rotation)
	{
		m_Rotation = rotation;
	}
	void Transform::SetScale(const XMFLOAT3& scale)
	{
		m_Scale = scale;
	}

	XMMATRIX Transform::GetWorldMatrix() const
	{
		XMMATRIX scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		XMMATRIX rotation = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		XMMATRIX translation = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		return scale * rotation * translation;
	}
}