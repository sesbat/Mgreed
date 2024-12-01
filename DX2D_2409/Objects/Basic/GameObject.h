#pragma once

class GameObject : public Transform
{
public:
    GameObject();
    ~GameObject();

    void Render(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    Material* GetMaterial() { return material; }

private:
    void Init();

protected:    
    Mesh* mesh;
    Material* material;

private:
    
    ID3D11Buffer* worldBuffer;    
};