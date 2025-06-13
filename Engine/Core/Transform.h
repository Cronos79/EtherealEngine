#pragma once
#include <DirectXMath.h>

namespace Ethereal
{
	class Transform
	{
	public:
		Transform();

		// Setters
		void SetPosition(const DirectX::XMFLOAT3& position);
		void SetRotation(const DirectX::XMFLOAT3& rotation); // Euler angles in radians
		void SetScale(const DirectX::XMFLOAT3& scale);

		// Getters
		const DirectX::XMFLOAT3& GetPosition() const
		{
			return m_Position;
		}
		const DirectX::XMFLOAT3& GetRotation() const
		{
			return m_Rotation;
		}
		const DirectX::XMFLOAT3& GetScale() const
		{
			return m_Scale;
		}

		DirectX::XMMATRIX GetWorldMatrix() const;

	private:
		DirectX::XMFLOAT3 m_Position;
		DirectX::XMFLOAT3 m_Rotation; // Pitch, Yaw, Roll
		DirectX::XMFLOAT3 m_Scale;
	};
}