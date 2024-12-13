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

Vector2 Camera::ScreenToWorld(Vector2 screenPos)
{
    Vector2 normalizedScreenPos;
    normalizedScreenPos.x = (screenPos.x / SCREEN_WIDTH) * 2.0f - 1.0f;
    normalizedScreenPos.y = 1.0f - (screenPos.y / SCREEN_HEIGHT) * 2.0f; 

    Matrix invViewProjection = XMMatrixInverse(nullptr, view * viewProjection.projection);

    XMFLOAT4 clipSpacePos(normalizedScreenPos.x, normalizedScreenPos.y, 0.0f, 1.0f);

    XMVECTOR clipVector = XMLoadFloat4(&clipSpacePos);
    XMVECTOR worldVector = XMVector4Transform(clipVector, invViewProjection);

    XMFLOAT4 worldPos;
    XMStoreFloat4(&worldPos, worldVector);

    return { worldPos.x, worldPos.y };
}

Vector2 Camera::WorldToScreen(Vector2 worldPos)
{
    XMFLOAT4 worldPos3D(worldPos.x, worldPos.y, 0.0f, 1.0f);

    XMVECTOR transformedPos = XMVector4Transform(XMLoadFloat4(&worldPos3D), view * viewProjection.projection);

    Vector2 screenPos;
    screenPos.x = (XMVectorGetX(transformedPos) + 1.0f) * 0.5f * SCREEN_WIDTH;
    screenPos.y = (1.0f - XMVectorGetY(transformedPos)) * 0.5f * SCREEN_HEIGHT;

    return screenPos;
}
