#include "Framework.h"

GameObject::GameObject()
{    
    Init();    
}

GameObject::~GameObject()
{
    delete material;
    delete mesh;

    worldBuffer->Release();
}

void GameObject::Render(D3D11_PRIMITIVE_TOPOLOGY type)
{
    if (!IsActive()) return;
    
    Matrix temp = XMMatrixTranspose(world);
    deviceContext->UpdateSubresource(worldBuffer, 0, nullptr, &temp, 0, 0);
    deviceContext->VSSetConstantBuffers(1, 1, &worldBuffer);    

    material->Set();

    mesh->Draw(type);
}

void GameObject::Init()
{   
    {
        //WorldBuffer
        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = sizeof(Matrix);
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

        device->CreateBuffer(&bufferDesc, nullptr, &worldBuffer);
    }

    mesh = new Mesh();
    material = new Material();
}
