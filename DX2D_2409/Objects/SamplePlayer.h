#pragma once
class SamplePlayer : public RigidbodyObject
{
    const float JUMP_POWER = 500.0f;

public:
    SamplePlayer();
    ~SamplePlayer();

    void Update();
    void Render();

    void SetLandCollider(int cnt, BoxCollider** collider) { colCount = cnt; landCollider = collider; }

private:
    void Move();
    void Jump();
    void CheckCollider();

private:
    Quad* image;

    int colCount;
    BoxCollider** landCollider;
};

