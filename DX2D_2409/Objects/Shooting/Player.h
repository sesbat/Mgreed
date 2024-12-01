#pragma once

class Player : public Quad
{
public:
    Player();
    ~Player();

    void Update();
    void Render();
    void PostRender();

    void Damage();

    CircleCollider* GetCollider() { return collider; }

private:
    void Move();
    void Rotate();
    void Fire();

private:
    float moveSpeed = 100.0f;
    float rotSpeed = 1.0f;
    int hp = 100;  

    Poly* firePos;
    float distance = 50.0f;

    CircleCollider* collider;

    Slider* hpBar;
};