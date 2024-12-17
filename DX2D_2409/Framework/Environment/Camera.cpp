#include "Framework.h"

Camera::Camera()
{
    tag = "Camera";

    Init();

    uiView = XMMatrixIdentity();
}

Camera::~Camera()
{
    viewProjectionBuffer->Release();
}

void Camera::Update()
{
    if (target)
        FollowMode();
    else
        FreeMode();

    UpdateWorld();
}

void Camera::SetViewProjection()
{
    view = XMMatrixInverse(nullptr, world);
    viewProjection.view = XMMatrixTranspose(view);

    deviceContext->UpdateSubresource(viewProjectionBuffer, 0, nullptr, &viewProjection, 0, 0);
    deviceContext->VSSetConstantBuffers(0, 1, &viewProjectionBuffer);
}

void Camera::SetUIView()
{
    viewProjection.view = uiView;

    deviceContext->UpdateSubresource(viewProjectionBuffer, 0, nullptr, &viewProjection, 0, 0);
    deviceContext->VSSetConstantBuffers(0, 1, &viewProjectionBuffer);
}

void Camera::Init()
{
    {
        //ConstBuffer
        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = sizeof(ViewProjection);
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

        device->CreateBuffer(&bufferDesc, nullptr, &viewProjectionBuffer);
    }

    viewProjection.view = XMMatrixIdentity();
    viewProjection.projection = XMMatrixOrthographicOffCenterLH(0, SCREEN_WIDTH,
        0, SCREEN_HEIGHT, -1, 1);

    viewProjection.projection = XMMatrixTranspose(viewProjection.projection);    
}

void Camera::FreeMode()
{
    if (KEY->Press(VK_RBUTTON))
    {
        if (KEY->Press('W'))
            Translate(Vector2::Up() * speed * DELTA);
        if (KEY->Press('S'))
            Translate(Vector2::Down() * speed * DELTA);
        if (KEY->Press('A'))
            Translate(Vector2::Left() * speed * DELTA);
        if (KEY->Press('D'))
            Translate(Vector2::Right() * speed * DELTA);
    }
}

void Camera::FollowMode()
{
    pos = target->GetGlobalPos() - CENTER;
}

Vector2 Camera::ScreenToWorld(const Vector2& screenPos)
{
    return pos + screenPos;
}

Vector2 Camera::WorldToScreen(const Vector2& worldPos)
{
    return worldPos - pos;
}
