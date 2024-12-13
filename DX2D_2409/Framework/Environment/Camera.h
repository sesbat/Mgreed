#pragma once

class Camera : public Transform
{
private:
    struct ViewProjection
    {
        Matrix view;
        Matrix projection;
    };

public:
    Camera();
    ~Camera();

    void Update();

    void SetViewProjection();
    void SetUIView();

    void SetTarget(Transform* target) { this->target = target; }

    Vector2 ScreenToWorld(Vector2 screenPos);
    Vector2 WorldToScreen(Vector2 worldPos);
private:
    void Init();

    void FreeMode();
    void FollowMode();

    
private:
    ViewProjection viewProjection;
    ID3D11Buffer* viewProjectionBuffer;

    Matrix view, uiView;

    float speed = 300.0f;

    Transform* target = nullptr;
};