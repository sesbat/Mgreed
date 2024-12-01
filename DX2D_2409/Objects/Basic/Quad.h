#pragma once

class Quad : public GameObject
{
public:
    Quad(Vector2 size = {100, 100});
    Quad(wstring textureFile, Vector2 startUV = Vector2(), Vector2 endUV = Vector2(1, 1));

    void UpdateSize(Vector2 size);

    Vector2 GetSize() { return size; }
private:
    void MakeMesh(Vector2 startUV, Vector2 endUV);

protected:   
    Vector2 size;    
};