#pragma once

#include <DirectXMath.h>
#include "EtherealEngine.h"

namespace Ethereal
{
	class ENGINE_API Camera
	{
	public:
		Camera();

		void SetPosition(const DirectX::XMFLOAT3& pos);
		void SetTarget(const DirectX::XMFLOAT3& target);
		void SetLens(float fovY, float aspect, float zn, float zf);

		const DirectX::XMMATRIX& GetView() const
		{
			return m_View;
		}
		const DirectX::XMMATRIX& GetProj() const
		{
			return m_Proj;
		}
		DirectX::XMMATRIX GetViewProj() const
		{
			return DirectX::XMMatrixMultiply(m_View, m_Proj);
		}
		void SetProjection(float fov, float aspectRatio, float near, float far)
		{

		}

	private:
		void UpdateView();

		DirectX::XMFLOAT3 m_Position;
		DirectX::XMFLOAT3 m_Target;

		DirectX::XMMATRIX m_View;
		DirectX::XMMATRIX m_Proj;
	};
}