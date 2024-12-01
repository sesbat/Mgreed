#pragma once

class Mario : public RigidbodyObject
{
private:
    const float JUMP_POWER = 500.0f; 

public:
    Mario();
    ~Mario();

    void Update();
    void Render();

    void SetLandCollider(BoxCollider* collider) { landCollider = collider; }

private:
    void Move();
    void Jump();
    void Land();
    void CollisionBrick();

private:    
    Quad* image;

    BoxCollider* landCollider;
};