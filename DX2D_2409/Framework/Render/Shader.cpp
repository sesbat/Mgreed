#include "Framework.h"

unordered_map<wstring, Shader*> Shader::shaders;

Shader::Shader(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    ID3DBlob* blob;
    D3DCompileFromFile(file.c_str(), nullptr, nullptr,
        "VS", "vs_5_0", flags, 0, &blob, nullptr);

    device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(),
        nullptr, &vertexShader);

    D3D11_INPUT_ELEMENT_DESC layoutDesc[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
        D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"UV", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,
        D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT layoutSize = ARRAYSIZE(layoutDesc);

    device->CreateInputLayout(layoutDesc, layoutSize,
        blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);

    blob->Release();

    D3DCompileFromFile(file.c_str(), nullptr, nullptr,
        "PS", "ps_5_0", flags, 0, &blob, nullptr);

    device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(),
        nullptr, &pixelShader);
}

Shader::~Shader()
{
    vertexShader->Release();
    pixelShader->Release();
    inputLayout->Release();
}

Shader* Shader::Add(wstring file)
{
    if (shaders.count(file) > 0)
        return shaders[file];

    shaders[file] = new Shader(file);

    return shaders[file];
}

void Shader::Delete()
{
    for (pair<wstring, Shader*> shader : shaders)
        delete shader.second;
}

void Shader::Set()
{
    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);
}
