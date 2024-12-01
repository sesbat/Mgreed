#pragma once

class Shader
{
private:
    Shader(wstring file);
    ~Shader();

public:
    static Shader* Add(wstring file);
    static void Delete();

    void Set();

private:
    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;
    ID3D11InputLayout* inputLayout;

    static unordered_map<wstring, Shader*> shaders;
};