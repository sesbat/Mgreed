#pragma once

class Bullet : public Quad
{
private:
    const float FPS = 10.0f;

public:
    Bullet();
    Bullet(wstring textureFile, Vector2 maxFrame);
    ~Bullet();

    void Update();
    void Render();

    void Fire(Float2 pos, Vector2 dir, Float4 color = Float4(1, 1, 1, 1));

    CircleCollider* GetCollider() { return collider; }

private:
    float delayTime = 1.0f / FPS;
    float frameTime = 0.0f;    

    UINT curFrameNum = 0;
    UINT maxFrameNum = 0;

    Vector2 curFrame;
    Vector2 maxFrame;

    float moveSpeed = 100.0f;
    Vector2 dir;

    CircleCollider* collider;
};