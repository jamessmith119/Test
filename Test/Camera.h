#ifndef __CAMERAHEADER__
#define __CAMERAHEADER__

#include "GraphicsEngine.h"

class Camera
{
	protected:
		DirectX::XMFLOAT4X4 viewMatrix;
		DirectX::XMFLOAT4X4 projectionMatrix;
		DirectX::XMFLOAT4X4 inverseViewMatrix;
		DirectX::XMFLOAT3 eyeDirection;
		DirectX::XMFLOAT3 lookAtDirection;
		DirectX::XMFLOAT3 upDirection;
		float cameraYawAngle;
		float cameraPitchAngle;
		float fieldofView;
		float aspectRatio;
		float nearPlane;
		float farPlane;

	public:
		Camera();
		void SetView(DirectX::XMFLOAT3, DirectX::XMFLOAT3, DirectX::XMFLOAT3);
		void SetProjection(float, float, float, float);
		void SetEye(DirectX::XMFLOAT3);
		void SetLookDirection(DirectX::XMFLOAT3);
};

#endif