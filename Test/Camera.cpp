#include "Camera.h"

Camera::Camera()
{
	SetView(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f));
	SetProjection(DirectX::XM_PI / 4, 1.0f, 1.0f, 1000.0f);
}

void Camera::SetView(DirectX::XMFLOAT3 eye, DirectX::XMFLOAT3 lookAt, DirectX::XMFLOAT3 up)
{
	eyeDirection = eye;
	lookAtDirection = lookAt;
	upDirection = up;

	// Calculate the view matrix.
    DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&eyeDirection), DirectX::XMLoadFloat3(&lookAtDirection), DirectX::XMLoadFloat3(&upDirection));
	DirectX::XMVECTOR det;
    DirectX::XMMATRIX inverseView = XMMatrixInverse(&det, view);
    DirectX::XMStoreFloat4x4(&viewMatrix, view);
    DirectX::XMStoreFloat4x4(&inverseViewMatrix, inverseView);

    // The axis basis vectors and camera position are stored inside the
    // position matrix in the 4 rows of the camera's world matrix.
    // To figure out the yaw/pitch of the camera, we just need the Z basis vector.
    DirectX::XMFLOAT3 zBasis;
    DirectX::XMStoreFloat3(&zBasis, inverseView.r[2]);

    cameraYawAngle = atan2f(zBasis.x, zBasis.z);

    float len = sqrtf(zBasis.z * zBasis.z + zBasis.x * zBasis.x);
    cameraPitchAngle = atan2f(zBasis.y, len);
}

void Camera::SetProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	// Set attributes for the projection matrix. 
    cameraFieldOfView = fieldOfView; 
    cameraAspectRatio = aspectRatio; 
    cameraNearPlane = nearPlane; 
    cameraFarPlane = farPlane; 
    DirectX::XMStoreFloat4x4(&projectionMatrix, DirectX::XMMatrixPerspectiveFovLH(cameraFieldOfView, cameraAspectRatio, cameraNearPlane, cameraFarPlane)); 

}

void Camera::SetEye(DirectX::XMFLOAT3 eye)
{
	SetView(eye, lookAtDirection, upDirection);
}

void Camera::SetLookDirection(DirectX::XMFLOAT3 direction)
{
	DirectX::XMFLOAT3 lookAt;
	lookAt.x = eyeDirection.x + direction.x;
	lookAt.y = eyeDirection.y + direction.y;
	lookAt.z = eyeDirection.z + direction.z;

	SetView(eyeDirection, lookAt, upDirection);
}

DirectX::XMMATRIX Camera::View()
{
    return DirectX::XMLoadFloat4x4(&viewMatrix);
}

DirectX::XMMATRIX Camera::Projection()
{
    return DirectX::XMLoadFloat4x4(&projectionMatrix);
}

DirectX::XMMATRIX Camera::World()
{
    return DirectX::XMLoadFloat4x4(&inverseViewMatrix);
}

DirectX::XMFLOAT3 Camera::Eye()
{
    return eyeDirection;
}

DirectX::XMFLOAT3 Camera::LookAt()
{
    return lookAtDirection;
}

float Camera::NearClipPlane()
{
    return cameraNearPlane;
}

float Camera::FarClipPlane()
{
    return cameraFarPlane;
}

float Camera::Pitch()
{
    return cameraPitchAngle;
}

float Camera::Yaw()
{
    return cameraYawAngle;
}