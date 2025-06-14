#include "Camera.h"

using namespace DirectX;

namespace Ethereal
{
	Camera::Camera()
	{
		m_Position = { 0.0f, 2.0f, -5.0f };
		m_Target = { 0.0f, 0.0f, 0.0f };
		SetLens(XM_PIDIV4, 1.777f, 0.1f, 100.0f); // default 16:9
		UpdateView();
	}

	void Camera::SetPosition(const XMFLOAT3& pos)
	{
		m_Position = pos;
		UpdateView();
	}

	void Camera::SetTarget(const XMFLOAT3& target)
	{
		m_Target = target;
		UpdateView();
	}

	void Camera::SetLens(float fovY, float aspect, float zn, float zf)
	{
		m_Proj = XMMatrixPerspectiveFovLH(fovY, aspect, zn, zf);
	}

	void Camera::UpdateView()
	{
		XMVECTOR eye = XMLoadFloat3(&m_Position);
		XMVECTOR target = XMLoadFloat3(&m_Target);
		XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		m_View = XMMatrixLookAtLH(eye, target, up);
	}
}